#include "gostring.h"
#include <cctype>
#include <algorithm>
#include <iterator>

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

    bool hasPrefix(const string &s, const string &prefix)
    {
        auto len1 = s.size();
        auto len2 = prefix.size();
        if (len1 < len2 || len2 == 0)
            return false;
        return std::equal(prefix.begin(), prefix.end(), s.begin());
    }

    bool hasSuffix(const string &s, const string &suffix)
    {
        auto len1 = s.size();
        auto len2 = suffix.size();
        if (len1 < len2 || len2 == 0)
            return false;
        return std::equal(suffix.rbegin(), suffix.rend(), s.rbegin());
    }

    bool contains(const string &s, const string &substr)
    {
        auto found = s.find(substr);
        return found == string::npos || s.empty() || substr.empty() ? false : true;
    }

    bool containsAny(const string &s, const string &chars)
    {
        return std::any_of(s.begin(), s.end(), [&](const char &c)
                           { return chars.find(c) == string::npos ? false : true; });
    }

    int index(const string &s, const string &sep)
    {
        auto found = s.find(sep);
        return found == string::npos || sep.empty() || s.empty() ? -1 : found;
    }

    int indexByte(const string &s, char c)
    {
        return index(s, string(1, c));
    }

    int indexAny(const string &s, const string &chars)
    {
        auto found = std::find_first_of(s.begin(), s.end(), chars.begin(), chars.end());
        return found == s.end() ? -1 : std::distance(s.begin(), found);
    }

    int indexFunc(const string &s, std::function<bool(const char &)> pred)
    {
        auto found = std::find_if(s.begin(), s.end(), pred);
        return found == s.end() ? -1 : std::distance(found, s.begin());
    }
}