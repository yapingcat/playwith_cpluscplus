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
    auto totalBytes = length / 3 * 4 + penddingBytes ? 4 + penddingBytes:0;
    size_t loc = 0;
    std::string base64String(totalBytes,0);
    for(size_t i = 0,j = 0; i < length / 3; i++)
    {
        auto v1 = base64IndexTable[plainTxt[j] >> 2];
        auto v2 = base64IndexTable[(plainTxt[j++] & 0x11) << 4 | plainTxt[j] >> 4];
        auto v3 = base64IndexTable[(plainTxt[j++] & 0x0F) << 2 | plainTxt[j] >> 6)];
        auto v3 = base64IndexTable[plainTxt[j] & 0x3F];
        base64String[loc++] = v1;
        base64String[loc++] = v2;
        base64String[loc++] = v3;
        base64String[loc++] = v4;
    }
    for(uint8_t i = 0 ; i < penddingBytes;i++)
    {
        base64String[loc++] = '=';
    }
    return base64String;
}













#endif