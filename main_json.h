#ifndef MAIN_JSON_H
#define MAIN_JSON_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <list>
#include <stdexcept>
using namespace std;

#include "json.h"
using namespace json_zbw::json;

#endif // MAIN_JSON_H

int main_json() {
    /*Json v1;
    Json v2 = true;
    Json v3 = 123;
    Json v4 = 1.23;
    Json v5 = "hello world";

    bool b = v2;
    int i = v3;
    double f = v4;
    const string & s = v5;*/

    /*Json arr;

    arr.append(true);
    arr.append(123);
    arr.append(1.23);
    arr.append("hello world");

    bool b = arr[0];
    int i = arr[1];
    double f = arr[2];
    const string& s = arr[3];

    cout << arr.str() << endl;

    Json obj;
    obj["布尔值"] = true;
    obj["整型值"] = 123;
    obj["浮点值"] = 1.23;
    obj["字符串"] = "hello world";
    obj["数组"] = arr;
    obj.remove("整型值");
    cout << obj.str() << endl;
    obj.clear();*/

    /*Json arr;
    arr.append(true);
    arr.append(123);
    arr.append(1.23);
    arr.append("hello world");
    for (auto it = arr.begin(); it != arr.end();it++) {
        cout << (*it).str() << endl;
    }*/

    /*Json arr;
    arr.append(true);
    arr.append(123);
    arr.append(1.23);
    arr.append("hello world");
    cout << arr.has(0) << endl;
    cout << arr.has(4) << endl;

    arr.remove(0);
    cout << arr.str() << endl;*/

    /*const string& str = "";
    Json v;
    v.parse(str);
    cout << v.str() << endl;*/

    Json v;

    ifstream fin("./example2.json", ios::in);
    ofstream fout("test.json", ios::out);
    stringstream  ss;

    ss << fin.rdbuf();
    const string& str = ss.str();

    v.parse(str);
    cout << v.str_p() << endl;
    fout << v.str_f() << endl;
    //cout << v["data"] << endl;
    //cout << v["cityNo"] << endl;


    return 0;
}
