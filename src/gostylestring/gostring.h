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

    //子串sep在字符串s中最后一次出现的位置，不存在则返回-1。
    int lastIndex(const string &s, const string &substr);

    //字符串chars中的任一字符在s中最后一次出现的位置，如不存在或者chars为空字符串则返回-1。
    int lastIndexAny(const string &s, const string &chars);

    //s中最后一个满足函数f的字符的位置i，不存在则返回-1
    int lastIndexFunc(const string &s, std::function<bool(const char &)> pred);

    //返回s中每个单词的首字母都改为标题格式的字符串拷贝
    string title(const string &s);

    //返回将所有字母都转为对应的大写版本的拷贝
    string toUpper(const string &s);

    //返回将所有字母都转为对应的小写版本的拷贝
    string toLower(const string &s);

    //返回count个s串联的字符串
    string repeat(const string &s, int count);

    //返回将s中前n个不重叠old子串都替换为new的新字符串，如果n<0会替换所有old子串
    string replace(const string &s, const string &oldstr, const string &newstr, int n);

    //将s的每一个char值r都替换为mapping(r)，返回这些字符值组成的字符串拷贝。如果mapping返回一个负值，将会丢弃该码值而不会被替换
    string mapstring(std::function<char(const char &)> mapping, const string &s);

    //返回将s前后端所有cutset包含的字符值都去掉的字符串
    string trim(const string &s, const string &cutset);

    //返回将s前后端所有空白都去掉的字符串
    string trimSpace(const string &s);

}

#endif
