#include <sstream>
using std::stringstream;

#include <stdexcept>

#include "json.h"
#include "parser.h"
using namespace json_zbw::json;

int t = 0;

Json::Json() : m_type(json_null)
{
}

Json::Json(Type type) : m_type(type)
{
    switch (m_type)
    {
    case json_null:
        break;
    case json_bool:
        m_value.m_bool = false;
        break;
    case json_int:
        m_value.m_int = 0;
        break;
    case json_double:
        m_value.m_double = 0.0;
        break;
    case json_string:
        m_value.m_string = new string("");
        break;
    case json_array:
        m_value.m_array = new std::vector<Json>();
        break;
    case json_object:
        m_value.m_object = new std::map<string, Json>();
    default:
        break;
    }
}

Json::Json(bool value) : m_type(json_bool)
{
    m_value.m_bool = value;
}

Json::Json(int value) : m_type(json_int)
{
    m_value.m_int = value;
}

Json::Json(double value) : m_type(json_double)
{
    m_value.m_double = value;
}

Json::Json(const char* value) : m_type(json_string)
{
    m_value.m_string = new string(value);
}

Json::Json(const string& value) : m_type(json_string)
{
    m_value.m_string = new string(value);
}

Json::Json(const Json& other) : m_type(json_null)
{
    copy(other);
}

Json::Json(Json&& other)
{
    swap(other);
}

Json::~Json()
{
    clear();
}

Json::Type Json::type() const
{
    return m_type;
}

bool Json::is_null() const
{
    return m_type == json_null;
}

bool Json::is_bool() const
{
    return m_type == json_bool;
}

bool Json::is_int() const
{
    return m_type == json_int;
}

bool Json::is_double() const
{
    return m_type == json_double;
}

bool Json::is_string() const
{
    return m_type == json_string;
}

bool Json::is_array() const
{
    return m_type == json_array;
}

bool Json::is_object() const
{
    return m_type == json_object;
}

bool Json::as_bool() const
{
    if (m_type == json_bool)
    {
        return m_value.m_bool;
    }
    std::cout << "function Json::asBool value type error" << std::endl;
    exit(0);
}

int Json::as_int() const
{
    if (m_type == json_int)
    {
        return m_value.m_int;
    }
    std::cout << "function Json::asInt value type error" << std::endl;
    exit(0);
}

double Json::as_double() const
{
    if (m_type == json_double)
    {
        return m_value.m_double;
    }
    std::cout << "function Json::asDouble value type error" << std::endl;
    exit(0);
}

string Json::as_string() const
{
    if (m_type == json_string)
    {
        return *(m_value.m_string);
    }
    std::cout << "function Json::asString value type error" << std::endl;
    exit(0);
}

//json类复制
void Json::copy(const Json& other)
{
    clear();
    m_type = other.m_type;
    switch (m_type)
    {
    case json_null:
    case json_bool:
    case json_int:
    case json_double:
        m_value = other.m_value;
        break;
    case json_string:
    {
        if (other.m_value.m_string != nullptr)
        {
            m_value.m_string = new string(*(other.m_value.m_string));
        }
    }
    break;
    case json_array:
    {
        if (other.m_value.m_array != nullptr)
        {
            m_value.m_array = new std::vector<Json>();
            for (auto it = (other.m_value.m_array)->begin(); it != (other.m_value.m_array)->end(); it++)
            {
                m_value.m_array->push_back(*it);
            }
        }
    }
    break;
    case json_object:
    {
        if (other.m_value.m_object != nullptr)
        {
            m_value.m_object = new std::map<string, Json>();
            for (auto it = (other.m_value.m_object)->begin(); it != (other.m_value.m_object)->end(); it++)
            {
                (*(m_value.m_object))[it->first] = it->second;
            }
        }
    }
    break;
    default:
        break;
    }
}

//json类交换
void Json::swap(Json& other)
{
    Type type = m_type;
    Value value = m_value;
    m_type = other.m_type;
    m_value = other.m_value;
    other.m_type = type;
    other.m_value = value;
}
//获取数组或对象的长度
int Json::size() const
{
    switch (m_type)
    {
    case json_array:
        return (m_value.m_array)->size();
    case json_object:
        return (m_value.m_object)->size();
    default:
        break;
    }
    std::cout << "function Json::size value type error" << std::endl;
    exit(0);
}
//数组或对象的判空
bool Json::empty() const
{
    switch (m_type)
    {
    case json_null:
        return true;
    case json_array:
        return (m_value.m_array)->empty();
    case json_object:
        return (m_value.m_object)->empty();
    default:
        break;
    }
    return false;
}

void Json::clear()
{
    switch (m_type)
    {
    case json_null:
    case json_bool:
    case json_int:
    case json_double:
        break;
    case json_string:
    {
        if (m_value.m_string != nullptr)
        {
            delete m_value.m_string;
            m_value.m_string = nullptr;
        }
    }
    break;
    case json_array:
    {
        if (m_value.m_array != nullptr)
        {
            for (auto it = (m_value.m_array)->begin(); it != (m_value.m_array)->end(); it++)
            {
                it->clear();
            }
            delete m_value.m_array;
            m_value.m_array = nullptr;
        }
    }
    break;
    case json_object:
    {
        if (m_value.m_object != nullptr)
        {
            for (auto it = (m_value.m_object)->begin(); it != (m_value.m_object)->end(); it++)
            {
                it->second.clear();
            }
            delete m_value.m_object;
            m_value.m_object = nullptr;
        }
    }
    break;
    default:
        break;
    }
    m_type = json_null;
}

bool Json::has(int index) const
{
    if (m_type != json_array)
    {
        return false;
    }
    int size = (m_value.m_array)->size();
    return (index >= 0) && (index < size);
}

bool Json::has(const char* key) const
{
    string name(key);
    return has(name);
}

bool Json::has(const string& key) const
{
    if (m_type != json_object)
    {
        return false;
    }
    return (m_value.m_object)->find(key) != (m_value.m_object)->end();
}

Json Json::get(int index) const
{
    if (!has(index))
    {
        return Json();
    }
    return (*(m_value.m_array))[index];
}

Json Json::get(const char* key) const
{
    if (!has(key))
    {
        return Json();
    }
    return (*(m_value.m_object))[key];
}

Json Json::get(const string& key) const
{
    if (!has(key))
    {
        return Json();
    }
    return (*(m_value.m_object))[key];
}

void Json::remove(int index)
{
    if (m_type != json_array)
    {
        return;
    }
    int size = (m_value.m_array)->size();
    if (index < 0 || index >= size)
    {
        return;
    }
    (m_value.m_array)->at(index).clear();
    (m_value.m_array)->erase((m_value.m_array)->begin() + index);
}

void Json::remove(const char* key)
{
    string name = key;
    remove(name);
}

void Json::remove(const string& key)
{
    if (m_type != json_object)
    {
        return;
    }
    auto it = (m_value.m_object)->find(key);
    if (it != (m_value.m_object)->end())
    {
        it->second.clear();
        (m_value.m_object)->erase(key);
    }
}

void Json::append(const Json& value)
{
    if (m_type != json_array)
    {
        clear();
        m_type = json_array;
        m_value.m_array = new std::vector<Json>();
    }
    (m_value.m_array)->push_back(value);
}

void Json::append(Json&& value)
{
    if (m_type != json_array)
    {
        clear();
        m_type = json_array;
        m_value.m_array = new std::vector<Json>();
    }
    (m_value.m_array)->push_back(std::move(value));
}

Json& Json::operator = (const Json& other)
{
    clear();
    copy(other);
    return *this;
}

Json& Json::operator = (Json&& other)
{
    swap(other);
    return *this;
}

bool Json::operator == (const Json& other)
{
    if (m_type != other.type())
    {
        return false;
    }
    switch (m_type)
    {
    case json_null:
        return true;
    case json_bool:
        return (m_value.m_bool == other.m_value.m_bool);
    case json_int:
        return (m_value.m_int == other.m_value.m_int);
    case json_double:
        return (m_value.m_double == other.m_value.m_double);
    case json_string:
        return *(m_value.m_string) == *(other.m_value.m_string);
    case json_array:
        return m_value.m_array == other.m_value.m_array;
    case json_object:
        return m_value.m_object == other.m_value.m_object;
    default:
        break;
    }
    return false;
}

bool Json::operator != (const Json& other)
{
    return !(*this == other);
}

Json& Json::operator [] (int index)
{
    if (m_type != json_array)
    {
        std::cout << "function [] not an array" << std::endl;
        exit(0);
    }
    if (index < 0)
    {
        std::cout << "function [] index less than 0" << std::endl;
        exit(0);
    }
    int size = (m_value.m_array)->size();
    if (index >= size)
    {
        std::cout << "function [] out of range" << std::endl;
        exit(0);
    }
    return (*(m_value.m_array))[index];
}

Json& Json::operator [] (const char* key)
{
    string name = key;
    return (*this)[name];
}

Json& Json::operator [] (const string& key)
{
    if (m_type != json_object)
    {
        clear();
        m_type = json_object;
        m_value.m_object = new std::map<string, Json>();
    }
    return (*(m_value.m_object))[key];
}

Json::operator bool()
{
    if (m_type != json_bool)
    {
        std::cout << "function Json::operator (bool) requires bool value" << std::endl;
        exit(0);
    }
    return m_value.m_bool;
}

Json::operator int()
{
    if (m_type != json_int)
    {
        std::cout << "function Json::operator (int) requires int value" << std::endl;
        exit(0);
    }
    return m_value.m_int;
}

Json::operator double()
{
    if (m_type != json_double)
    {
        std::cout << "function Json::operator (double) requires double value" << std::endl;
        exit(0);
    }
    return m_value.m_double;
}

Json::operator string()
{
    if (m_type != json_string)
    {
        std::cout << "function Json::operator (string) requires string value" << std::endl;
        exit(0);
    }
    return *(m_value.m_string);
}

Json::operator string() const
{
    if (m_type != json_string)
    {
        std::cout << "function Json::operator (string) requires string value" << std::endl;
        exit(0);
    }
    return *(m_value.m_string);
}
//解析json文件中的字符串
void Json::parse(const string& str)
{
    Parser parser;
    parser.load(str);
    *this = parser.parse();
}

//窗口输出
string Json::str_p() const
{
    stringstream ss;

    switch (m_type)
    {
    case json_null:
        ss << "\033[33;1mnull\033[0m";
        break;
    case json_bool:
        if (m_value.m_bool)
        {
            ss << "\033[33;1mtrue\033[0m";
        }
        else
        {
            ss << "\033[33;1mfalse\033[0m";
        }
        break;
    case json_int:
        ss << "\033[33;1m" << m_value.m_int << "\033[0m";
        break;
    case json_double:
        ss << "\033[33;1m" << m_value.m_double << "\033[0m";
        break;
    case json_string:
        ss << "\"\033[33;1m" << *(m_value.m_string) << "\033[0m\"";
        break;
    case json_array:
    {
        ss << "[\n";
        t++;
        for (auto it = (m_value.m_array)->begin(); it != (m_value.m_array)->end(); it++)
        {
            if (it != (m_value.m_array)->begin())
            {
                ss << ",\n";
            }
            for (int i = 0;i < t;i++) { ss << "\t"; }
            ss << "\033[33;1m" << (*it).str_p() << "\033[0m";
        }
        t--;
        ss << "\n";
        for (int i = 0;i < t;i++) { ss << "\t"; }
        ss << "]";
    }
    break;
    case json_object:
    {
        ss << "{\n";
        t++;
        for (auto it = (m_value.m_object)->begin(); it != (m_value.m_object)->end(); it++)
        {
            if (it != (m_value.m_object)->begin())
            {
                ss << ",\n";
            }
            for (int i = 0;i < t;i++) { ss << "\t"; }
            ss << "\"\033[36;1m" << it->first << "\033[0m\":" <<it->second.str_p();
        }
        t--;
        ss << "\n";
        for (int i = 0;i < t;i++) { ss << "\t"; }
        ss << "}";
    }
    break;
    default:
        break;
    }
    return ss.str();
}

//文件输出
string Json::str_f() const
{
    stringstream ss;
    switch (m_type)
    {
    case json_null:
        ss << "null";
        break;
    case json_bool:
        if (m_value.m_bool)
        {
            ss << "true";
        }
        else
        {
            ss << "false";
        }
        break;
    case json_int:
        ss << m_value.m_int;
        break;
    case json_double:
        ss << m_value.m_double;
        break;
    case json_string:
        ss << "\"" << *(m_value.m_string) << "\"";
        break;
    case json_array:
    {
        ss << "[\n";
        t++;
        for (auto it = (m_value.m_array)->begin(); it != (m_value.m_array)->end(); it++)
        {
            if (it != (m_value.m_array)->begin())
            {
                ss << ",\n";
            }
            for (int i = 0;i < t;i++) { ss << "\t"; }
            ss << (*it).str_f();
        }
        t--;
        ss << "\n";
        for (int i = 0;i < t;i++) { ss << "\t"; }
        ss << "]";
    }
    break;
    case json_object:
    {
        ss << "{\n";
        t++;
        for (auto it = (m_value.m_object)->begin(); it != (m_value.m_object)->end(); it++)
        {
            if (it != (m_value.m_object)->begin())
            {
                ss << ",\n";
            }
            for (int i = 0;i < t;i++) { ss << "\t"; }
            ss << "\"" << it->first << "\":" << it->second.str_f();
        }
        t--;
        ss << "\n";
        for (int i = 0;i < t;i++) { ss << "\t"; }
        ss << "}";
    }
    break;
    default:
        break;
    }
    return ss.str();
}
