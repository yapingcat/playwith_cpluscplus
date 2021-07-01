#ifndef GO_STRING_H
#define GO_STRING_H

#include <string>
#include <vector>

using std::string;
using std::vector;

//golang 风格的字符串操作函数
//模仿 golang strings 标准库
namespace gostring
{
    //统计不重叠字串在s中出现的次数
    int count(const string &s, const string &substr);

    //忽略大小写，比较两个 字符串大小
    bool equalfold(const string &s, const string &t);

    //以连续的空格符 为分隔符，分割字符串
    std::vector<string> fields(const string &s);
}

#endif
