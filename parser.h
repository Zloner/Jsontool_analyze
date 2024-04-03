#pragma once
#include "json.h"

namespace json_zbw {
    namespace json {

        class Parser
        {
        public:
            Parser();
            ~Parser();

            //将str的值赋给m_str
            void load(const string& str);
            //解析函数
            Json parse();

        private:
            //跳过无用字符
            void skip_white_space();
            //获取当前字符，并指向下一个字符
            char get_next_token();

            //各类型单独解析
            Json parse_null();
            Json parse_bool();
            Json parse_number();
            string parse_string();
            Json parse_array();
            Json parse_object();

            bool in_range(int x, int lower, int upper)
            {
                return (x >= lower && x <= upper);
            }

        private:
            string m_str;   //存储Json文件的字符串
            size_t m_idx;   //解析字符串的位置
        };

    }
}
