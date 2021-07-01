#include "gostring.h"
#include <cctype>

namespace gostring
{
    int count(const string &s, const string &substr)
    {
        string::size_type pos = s.find(substr);
        auto len = substr.size();
        if (len == 0)
        {
            return s.size() + 1;
        }
        int foundN = 0;
        while (pos != string::npos)
        {
            foundN++;
            pos += len;
            pos = s.find(substr, pos);
        }
        return foundN == 0 ? (substr == "" ? len + 1 : 0) : foundN;
    }

    bool equalfold(const string &s, const string &t)
    {
        auto l1 = s.size();
        auto l2 = t.size();
        if (l1 != l2)
        {
            return false;
        }
        for (auto i = 0; i < l1; i++)
        {
            if (std::isalpha(s[i]) && std::isalpha(t[i]))
            {
                auto delta = s[i] - t[i];
                if (delta != 0 && delta != 32 && delta != -32)
                {
                    return false;
                }
            }
            else if (s[i] != t[i])
            {
                return false;
            }
        }
        return true;
    }

    std::vector<string> fields(const string &s)
    {
        std::vector<string> a;
        auto notspace = s.find_first_not_of(' ');
        while (notspace != string::npos)
        {
            auto space = s.find_first_of(' ', notspace);
            if (space == string::npos)
            {
                a.push_back(s.substr(notspace));
                break;
            }
            else
            {
                a.push_back(s.substr(notspace, space - notspace));
                notspace = s.find_first_not_of(' ', space);
            }
        }
        return a;
    }
}