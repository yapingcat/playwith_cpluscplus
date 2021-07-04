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

    int lastIndex(const string &s, const string &substr)
    {
        auto found = s.find(substr);
        return found == string::npos || substr.empty() ? -1 : found;
    }

    int lastIndexAny(const string &s, const string &chars)
    {
        auto found = std::find_first_of(s.rbegin(), s.rend(), chars.rbegin(), chars.rend());
        if (found == s.rend())
            return -1;
        std::advance(found, chars.size());
        return std::distance(s.begin(), found.base());
    }

    int lastIndexFunc(const string &s, std::function<bool(const char &)> pred)
    {
        auto found = std::find_if(s.rbegin(), s.rend(), pred);
        return found == s.rend() ? -1 : std::distance(s.begin(), std::prev(found.base()));
    }

    string title(const string &s)
    {
        string s2 = s;
        bool preCharIsAlpha = false;
        for (int i = 0; i < s2.size(); i++)
        {
            if (std::isalpha(s2[i]) && !preCharIsAlpha)
            {
                s2[i] = std::toupper(s2[i]);
                preCharIsAlpha = true;
            }
            else if (!std::isalpha(s2[i]))
            {
                preCharIsAlpha = false;
            }
        }
        return s2;
    }

    string toUpper(const string &s)
    {
        string s2 = s;
        for (auto &c : s2)
        {
            if (std::isalpha(c))
            {
                c = std::toupper(c);
            }
        }
        return s2;
    }

    string toLower(const string &s)
    {
        string s2 = s;
        for (auto &c : s2)
        {
            if (std::isalpha(c))
            {
                c = std::tolower(c);
            }
        }
        return s2;
    }

    string repeat(const string &s, int count)
    {
        string repeatstr;
        repeatstr.reserve(s.size() * (count < 0 ? 0 : count));
        for (int i = 0; i < count; i++)
        {
            repeatstr += s;
        }
        return repeatstr;
    }

    string replace(const string &s, const string &oldstr, const string &newstr, int n)
    {
        string replacedstr = s;
        auto len = oldstr.size();
        while ((uint32_t)n-- > 0)
        {
            auto found = replacedstr.find(oldstr);
            if (found == string::npos)
            {
                break;
            }
            replacedstr.replace(found, len, newstr);
        }
        return replacedstr;
    }

    string mapstring(std::function<char(const char &)> mapping, const string &s)
    {
        string newMapStr = s;
        for (auto &c : newMapStr)
        {
            c = mapping(c);
        }
        return newMapStr;
    }

    string trim(const string &s, const string &cutset)
    {
        string fronttrimstr;
        int len = s.size();
        int beg = 0;
        for (; beg < len; beg++)
        {
            if (std::isalpha(s[beg]))
            {
                break;
            }
            if (std::find(cutset.begin(), cutset.end(), s[beg]) != cutset.end())
            {
                continue;
            }
            fronttrimstr += s[beg];
        }
        int end = len - 1;
        string backtrimstr;
        for (; end >= 0; end--)
        {
            if (std::isalpha(s[end]))
            {
                break;
            }
            if (std::find(cutset.begin(), cutset.end(), s[end]) != cutset.end())
            {
                continue;
            }
            backtrimstr += s[end];
        }
        string trimstr = fronttrimstr + s.substr(beg, end - beg + 1) + backtrimstr;
        return trimstr;
    }

    string trimSpace(const string &s)
    {
        int beg = 0;
        int len = s.size();
        for (; beg < len; beg++)
        {
            if (!std::isspace(s[beg]))
            {
                break;
            }
        }

        int end = len - 1;
        for (; end >= 0; end--)
        {
            if (!std::isspace(s[end]))
            {
                break;
            }
        }
        return s.substr(beg, end - beg + 1);
    }
}
