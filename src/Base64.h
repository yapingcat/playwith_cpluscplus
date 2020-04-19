#ifndef BASE64_H
#define BASE64_H

#include <array>
#include <string>

static std::array<char,64> base64IndexTable =
{
    'A','B','C','D','E','F','G','H',
    'I','J','K','L','M','N','O','P',
    'Q','R','S','T','U','V','W','X',
    'Y','Z','a','b','c','d','e','f',
    'g','h','i','j','k','l','m','n',
    'o','p','q','r','s','t','u','v',
    'w','x','y','z','0','1','2','3',
    '4','5','6','7','8','9','+','/'
};


static std::string base64Encode(const std::string& plainTxt)
{
    auto length = plainTxt.size();
    auto penddingBytes = length % 3 ? 3 - length % 3 : 0;
    auto totalBytes = length / 3 * 4 + (penddingBytes ? 4 + penddingBytes:0);
    size_t loc = 0;
    std::string base64String(totalBytes,0);
    for(size_t i = 0,j = 0; i < length / 3; i++)
    {
        auto v1 = base64IndexTable[plainTxt[j] >> 2];
        auto v2 = base64IndexTable[(plainTxt[j++] & 0x03) << 4 | plainTxt[j] >> 4];
        auto v3 = base64IndexTable[(plainTxt[j++] & 0x0F) << 2 | plainTxt[j] >> 6];
        auto v4 = base64IndexTable[plainTxt[j++] & 0x3F];
        base64String[loc++] = v1;
        base64String[loc++] = v2;
        base64String[loc++] = v3;
        base64String[loc++] = v4;
    }
    if(penddingBytes == 1)
    {
        auto v1 = base64IndexTable[plainTxt[length - 2] >> 2];
        auto v2 = base64IndexTable[(plainTxt[length - 2] & 0x03) << 4 | plainTxt[length - 1] >> 4];
        auto v3 = base64IndexTable[(plainTxt[length - 1] & 0x0F) << 2];
        base64String[loc++] = v1;
        base64String[loc++] = v2;
        base64String[loc++] = v3;
    }
    else if(penddingBytes == 2)
    {
        auto v1 = base64IndexTable[plainTxt[length - 1] >> 2];
        auto v2 = base64IndexTable[(plainTxt[length - 1] & 0x03) << 4];
        base64String[loc++] = v1;
        base64String[loc++] = v2;
    }

    for(uint8_t i = 0 ; i < penddingBytes;i++)
    {
        base64String[loc++] = '=';
    }
    return base64String;
}

static std::string base64Decode(const std::string& base64String)
{
    auto length = base64String.size();
    decltype(length) loc = 0;
    std::string plainTxt(length / 4,0);
    auto calcIdx = [](const char &c){ 
        int idx = 0;
        if( c >= 'A' && c <= 'Z')
            idx = c - 'A';
        else if(c >= 'a' && c <= 'z')
            idx = c - 'a';
        else if(c == '+')
            idx = 62;
        else if(c == '/')
            idx = 63;
        else
            idx = -1;
        return idx;
    };
    for(size_t i = 0,j = 0; i < length / 4; i++)
    {
        auto idx1 = calcIdx(base64String[j++]);
        auto idx2 = calcIdx(base64String[j++]);
        auto idx3 = calcIdx(base64String[j++]);
        auto idx4 = calcIdx(base64String[j++]);
        
        auto v1 =  idx1 << 2 | idx2 >> 4;
        plainTxt[loc++] = v1;
        if(idx3 == -1)
        {
            plainTxt.pop_back();
            plainTxt.pop_back();
            break;
        }
            
        auto v2 = idx2 << 4 | idx3 >> 2;
        plainTxt[loc++] = v2;
        if(idx4 == -1)
        {
            plainTxt.pop_back();
            break;
        }
        auto v3 = calcIdx(base64String[j++]) << 6 | calcIdx(base64String[j]);
        plainTxt[loc++] = v2;
    }
    return plainTxt;
}













#endif
