#include <string.h>
#include <stdexcept>
#include <cstdlib>

#include "parser.h"
using namespace json_zbw::json;

Parser::Parser() : m_idx(0)
{
}

Parser::~Parser()
{
}

void Parser::load(const string& str)
{
    m_str = str;
    m_idx = 0;
}

//跳过无用字符
void Parser::skip_white_space()
{
    while (m_str[m_idx] == ' ' || m_str[m_idx] == '\r' || m_str[m_idx] == '\n' || m_str[m_idx] == '\t')
        m_idx++;
}

//获取当前字符，并指向下一字符
char Parser::get_next_token()
{
    skip_white_space();
    return m_str[m_idx++];
}

//解析函数
Json Parser::parse()
{
    char ch = get_next_token();
    switch (ch)
    {
    case 'n'://null
    case 'N'://NULL
        m_idx--;//标记索引回退一格，将当前位包含在检测范围内
        return parse_null();
    case 't'://true
    case 'T'://TRUE
    case 'f'://false
    case 'F'://FALSE
        m_idx--;
        return parse_bool();
    case '-'://数字
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
        m_idx--;
        return parse_number();
    case '"'://字符串
        return Json(parse_string());
    case '['://数组
        return parse_array();
    case '{'://对象
        return parse_object();
    default:
        break;
    }
    //出现其它字符跳出
    std::cout << "unexpected character in parse json" << std::endl;
    exit(0);
}

//空值解析函数
Json Parser::parse_null()
{
    if (m_str.compare(m_idx, 4, "null") == 0 || m_str.compare(m_idx, 4, "NULL") == 0)
    {
        m_idx += 4;
        return Json();
    }
    //下四位与NULL或null不同
    std::cout << "parse null error" << std::endl;
    exit(0);
}

//布尔值解析函数
Json Parser::parse_bool()
{
    if (m_str.compare(m_idx, 4, "true") == 0 || m_str.compare(m_idx, 4, "TRUE") == 0)
    {
        m_idx += 4;
        return Json(true);
    }
    if (m_str.compare(m_idx, 5, "false") == 0 || m_str.compare(m_idx, 5, "FALSE") == 0)
    {
        m_idx += 5;
        return Json(false);
    }
    //接下来的字符串不是bool值
    std::cout << "parse bool error" << std::endl;
    exit(0);
}


//数字解析函数
Json Parser::parse_number()
{
    size_t pos = m_idx;

    if (m_str[m_idx] == '-')
        m_idx++;

    //整数部分
    if (m_str[m_idx] == '0')
    {
        m_idx++;
    }
    else if (in_range(m_str[m_idx], '1', '9'))
    {
        m_idx++;
        while (in_range(m_str[m_idx], '0', '9'))
        {
            m_idx++;
        }
    }
    else
    {
        //该字符不在0-9范围内
        std::cout << "invalid character in number" << std::endl;
        exit(0);
    }

    if (m_str[m_idx] != '.')
    {
        return Json(std::atoi(m_str.c_str() + pos));
    }

    //小数部分
    m_idx++;
    if (!in_range(m_str[m_idx], '0', '9'))
    {
        //该字符不在0-9范围内
        std::cout << "at least one digit required in fractional part" << std::endl;
        exit(0);
    }
    while (in_range(m_str[m_idx], '0', '9'))
    {
        m_idx++;
    }
    return Json(std::atof(m_str.c_str() + pos));
}

//字符串解析函数
string Parser::parse_string()
{
    int pos = m_idx;    //保存起始位置
    while (true)
    {
        if (m_idx == m_str.size())
        {
            std::cout << "unexpected end of input in string" << std::endl;
            exit(0);
        }

        char ch = m_str[m_idx++];
        //读到”跳出循环
        if (ch == '"')
        {
            break;
        }
        //遇到转义字符
        if (ch == '\\')
        {
            ch = m_str[m_idx++];
            switch (ch)
            {
            case 'b'://退格
            case 't'://缩进
            case 'n'://换行
            case 'f'://换页
            case 'r'://回车
            case '"'://引号
            case '\\':
                break;
            case 'u'://接4字节
                m_idx += 4;
                break;
            default:
                break;
            }
        }
    }
    return m_str.substr(pos, m_idx - pos - 1);
}

//数组解析函数
Json Parser::parse_array()
{
    Json arr(Json::json_array);
    char ch = get_next_token();
    //以 ] 作为数组结束的标志
    if (ch == ']')
    {
        return arr;
    }
    m_idx--;
    while (true)
    {
        //解析单独元素后，加到数组类型中
        arr.append(parse());
        ch = get_next_token();
        if (ch == ']')
        {
            break;
        }
        //缺少“，”
        if (ch != ',')
        {
            std::cout << "expected ',' in array" << std::endl;
            exit(0);
        }
    }
    return arr;
}

//对象解析函数
Json Parser::parse_object()
{
    Json obj(Json::json_object);
    char ch = get_next_token();
    //以 } 作为数组结束的标志
    if (ch == '}')
    {
        return obj;
    }
    m_idx--;
    while (true)
    {
        ch = get_next_token();
        //缺少 ”
        if (ch != '"')
        {
            std::cout << "expected '\"' in object" << std::endl;
            exit(0);
        }
        string key = parse_string();
        ch = get_next_token();
        //缺少“：”
        if (ch != ':')
        {
            std::cout << "expected ':' in object" << std::endl;
            exit(0);
        }
        obj[key] = parse();
        ch = get_next_token();
        if (ch == '}')
        {
            break;
        }
        //缺少“，”
        if (ch != ',')
        {
            std::cout << "expected ',' in object" << std::endl;
            exit(0);
        }
    }
    return obj;
}
