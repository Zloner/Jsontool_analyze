#pragma once

#include <iostream>
#include <string>
using std::string;

#include <ostream>
using std::ostream;

#include <vector>
#include <map>

namespace json_zbw {
    namespace json {

        class Json
        {
        public:
            //类型定义
            enum Type
            {
                json_null = 0,  //空类型
                json_bool,      //布尔类型
                json_int,       //整型
                json_double,    //浮点型
                json_string,    //字符串
                json_array,     //数组类型
                json_object     //对象类型
            };

            //构造函数
            Json();
            Json(Type type);
            Json(bool value);
            Json(int value);
            Json(double value);
            Json(const char* value);
            Json(const string& value);
            Json(const Json& other);
            Json(Json&& other);
            ~Json();

            //返回当前类型
            Type type() const;
            //类型判断
            bool is_null() const;
            bool is_bool() const;
            bool is_int() const;
            bool is_double() const;
            bool is_string() const;
            bool is_array() const;
            bool is_object() const;
            //返回对应元素类型的值
            bool as_bool() const;
            int as_int() const;
            double as_double() const;
            string as_string() const;

            //获取当前数组或对象的元素个数
            int size() const;

            //如果为空数组、空对象、NULL，返回true
            bool empty() const;

            //清空json变量的内容
            void clear();

            //判断索引对应的值是否存在
            bool has(int index) const;
            bool has(const char* key) const;
            bool has(const string& key) const;
            //获取对应索引的值
            Json get(int index) const;
            Json get(const char* key) const;
            Json get(const string& key) const;
            //移除对应索引的值
            void remove(int index);
            void remove(const char* key);
            void remove(const string& key);

            //像数组末尾添加元素
            void append(const Json& value);
            void append(Json&& value);

            //运算符重载
            Json& operator = (const Json& other);
            Json& operator = (Json&& other);

            bool operator == (const Json& other);
            bool operator != (const Json& other);

            Json& operator [] (int index);
            Json& operator [] (const char* key);
            Json& operator [] (const string& key);

            friend ostream& operator << (ostream& os, const Json& json)
            {
                os << json.str_p();
                return os;
            }
            //获取特定元素类型的值
            operator bool();
            operator int();
            operator double();
            operator string();
            operator string() const;

            //Json解析函数
            void parse(const string& str);
            //Json格式化函数
            string str_p() const;//包含字体颜色
            string str_f() const;//不包含字体颜色

            typedef std::vector<Json>::iterator iterator;
            iterator begin()
            {
                return (m_value.m_array)->begin();
            }
            iterator end()
            {
                return (m_value.m_array)->end();
            }

        private:
            //Json对象的复制
            void copy(const Json& other);
            //Json对象与另一个对象交换值
            void swap(Json& other);

        private:
            //值定义
            union Value
            {
                bool m_bool;                        //布尔值
                int m_int;                          //整型值
                double m_double;                    //浮点值
                std::string* m_string;              //字符串值
                std::vector<Json>* m_array;         //数组值
                std::map<string, Json>* m_object;   //对象值
            };

            Type m_type;
            Value m_value;
        };

    }
}
