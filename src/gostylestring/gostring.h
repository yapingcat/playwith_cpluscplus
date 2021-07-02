#ifndef GO_STRING_H
#define GO_STRING_H

#include <string>
#include <vector>
#include <functional>

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

    //判断s是否有前缀字符串prefix
    bool hasPrefix(const string &s, const string &prefix);

    //判断s是否有后缀字符串suffix
    bool hasSuffix(const string &s, const string &suffix);

    //判断字符串s是否包含子串substr
    bool contains(const string &s, const string &substr);

    //判断字符串s是否包含字符串chars中的任一字符
    bool containsAny(const string &s, const string &chars);

    //子串sep在字符串s中第一次出现的位置，不存在则返回-1
    int index(const string &s, const string &sep);

    //字符c在s中第一次出现的位置，不存在则返回-1
    int indexByte(const string &s, char c);

    //字符串chars中的任一字符在s中第一次出现的位置，如果不存在或者chars为空字符串则返回-1
    int indexAny(const string &s, const string &chars);

    //s中第一个满足函数f的位置i，不存在则返回-1
    int indexFunc(const string &s, std::function<bool(const char &)> pred);
}

#endif
