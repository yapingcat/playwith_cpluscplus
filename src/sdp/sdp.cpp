#include "sdp.h"
#include "../StringUtil.h"


void Origin::parser(const std::string& orgin)
{
    std::string::size_type pos = 0;
    auto takeString = [&]() -> std::string {

        std::string value = "";
        auto pos1 = orgin.find(' ',pos);
        if(pos1 == std::string::npos)
        {
            value = orgin.substr(pos);
            pos = orgin.size();
        }
        else
        {
            value = orgin.substr(pos,pos1 - pos);
            pos = pos1 + 1;
        }
        return value;
    };

    username        = takeString();
    sess_id         = takeString();
    sess_version    = takeString();
    nettype         = takeString();
    addrtype        = takeString();
    unicast_address = takeString();
}

void ConnectionData::parser(const std::string& connectionData)
{
    std::string::size_type pos = 0;
    auto takeString = [&]() -> std::string {

        std::string value = "";
        auto pos1 = connectionData.find(' ',pos);
        if(pos1 == std::string::npos)
        {
            value = connectionData.substr(pos);
            pos = connectionData.size();
        }
        else
        {
            value = connectionData.substr(pos,pos1 - pos);
            pos = pos1 + 1;
        }
        return value;
    };
    nettype             = takeString();
    addrtype            = takeString();
    connection_address  = takeString();
}

void BandWidth::parser(const std::string& bandWidth)
{
    std::string::size_type pos = 0;
    auto takeString = [&]() -> std::string {

        std::string value = "";
        auto pos1 = bandWidth.find(' ',pos);
        if(pos1 == std::string::npos)
        {
            value = bandWidth.substr(pos);
            pos = bandWidth.size();
        }
        else
        {
            value = bandWidth.substr(pos,pos1 - pos);
            pos = pos1 + 1;
        }
        return value;
    };

    bwtype    =  takeString();
    bandwidth =  takeString();
}

void Timing::parser(const std::string& timing)
{
    std::string::size_type pos = 0;
    auto takeString = [&]() -> std::string {

        std::string value = "";
        auto pos1 = timing.find(' ',pos);
        if(pos1 == std::string::npos)
        {
            value = timing.substr(pos);
            pos = timing.size();
        }
        else
        {
            value = timing.substr(pos,pos1 - pos);
            pos = pos1 + 1;
        }
        return value;
    };

    start_time  =  takeString();
    stop_time   =  takeString();
}

void RepeatTimes::parser(const std::string& timing)
{
    std::string::size_type pos = 0;
    auto takeString = [&]() -> std::string {

        std::string value = "";
        auto pos1 = timing.find(' ',pos);
        if(pos1 == std::string::npos)
        {
            value = timing.substr(pos);
            pos = timing.size();
        }
        else
        {
            value = timing.substr(pos,pos1 - pos);
            pos = pos1 + 1;
        }
        return value;
    };

    repeat_interval         =  takeString();
    active_duration         =  takeString();
    offsets_from_start_time =  takeString();
}

void TimeZones::parser(const std::string& timeZones)
{
    std::string::size_type pos = 0;
    auto takeString = [&]() -> std::string {

        std::string value = "";
        auto pos1 = timeZones.find(' ',pos);
        if(pos1 == std::string::npos)
        {
            value = timeZones.substr(pos);
            pos = timeZones.size();
        }
        else
        {
            value = timeZones.substr(pos,pos1 - pos);
            pos = pos1 + 1;
        }
        return value;
    };
    while(pos != timeZones.size())
    {
        std::string adjustment_time  = takeString();
        std::string offset           = takeString();
        adj_Offset.push_back(std::make_tuple(adjustment_time,offset));
    }
}

void EncryptionKeys::parser(const std::string& encryption)
{
    if(encryption.find(":") != std::string::npos)
    {
        method = encryption.substr(0,encryption.find(":"));
        encryption_key = encryption.substr(encryption.find(":") + 1);
    }
    else
    {
        method = encryption;
    }
}

void Media::parser(const std::string& mediaDescribe)
{
    std::string::size_type pos = 0;
    auto takeString = [&]() -> std::string {

        std::string value = "";
        auto pos1 = mediaDescribe.find(' ',pos);
        if(pos1 == std::string::npos)
        {
            value = mediaDescribe.substr(pos);
            pos = mediaDescribe.size();
        }
        else
        {
            value = mediaDescribe.substr(pos,pos1 - pos);
            pos = pos1 + 1;
        }
        return value;
    };

    media                = takeString();
    std::string portstr  = takeString();
    proto                = takeString();
    std::string fmtLists = takeString();
    
    if(portstr.find("/") != std::string::npos)
    {
       int pn = std::stoi(portstr.substr(portstr.find("/") + 1)); 
       int basePort = std::stoi(portstr.substr(0,portstr.find("/")));
       for(int i = 0; i < pn; pn ++)
       {
           ports.push_back(basePort + i);
       }
    }
    else
    {
        ports.push_back(std::stoi(portstr));
    }
   
}

void Attribute::parser(const std::string& attr)
{
    splitInTwoPart(attr,':',name,value);
}


Sdp parser(const std::string& sdp)
{
    Sdp tmpSdp;
    int mediaProcess = 0;
    auto parserAttr = [&](const std::string& attr){
        Attribute attribute;
        attribute.parser(attr);
        if(mediaProcess)
        {
            tmpSdp.mediaDescriptions[mediaProcess - 1].attrs.push_back(attribute);
        }
        else
        {
            tmpSdp.sessionDescription.attrs.push_back(attribute);
        }
    };

    readLines(sdp,[&](const char* sdp,size_t len){
        std::string name = "";
        std::string value = "";
        splitInTwoPart({sdp,len},'=',name,value);
        if(name == "v")         tmpSdp.sessionDescription.version       = std::stoi(value);
        else if(name == "o")    tmpSdp.sessionDescription.origin.parser(value);
        else if(name == "s")    tmpSdp.sessionDescription.sessionName   = value;
        else if(name == "i")    tmpSdp.sessionDescription.sessionInfo   = value;
        else if(name == "u")    tmpSdp.sessionDescription.Uri           = value;
        else if(name == "e")    tmpSdp.sessionDescription.email_address = value;
        else if(name == "p")    tmpSdp.sessionDescription.phone_number  = value;
        else if(name == "t")    tmpSdp.timeDescription.time.parser(value);
        else if(name == "r")    tmpSdp.timeDescription.repeat.parser(value);
        else if(name == "k")    tmpSdp.sessionDescription.keys.parser(value);
        else if(name == "a")    parserAttr(value);
        else if(name == "m")    { 
                                    mediaProcess++; 
                                    MediaDescription md; 
                                    md.media.parser(value); 
                                    tmpSdp.mediaDescriptions.push_back(md);
                                }
    });
    return tmpSdp;
}

#ifdef SDP_TEST
#include <iostream>

    int main()
    {
        std::string sdp =  "v=0\r\n"
                        "o=alice 2890844526 2890844526 IN IP4 host.anywhere.com\r\n"
                        "s=Rtc Server\r\n"
                        "c=IN IP4 host.anywhere.com\r\n"
                        "t=0 0\r\n"
                        "m=audio 49170 RTP/AVP 0\r\n"
                        "a=rtpmap:0 PCMU/8000\r\n"
                        "m=video 51372 RTP/AVP 31\r\n"
                        "a=rtpmap:31 H261/90000\r\n"
                        "m=video 53000 RTP/AVP 32\r\n"
                        "a=rtpmap:32 MPV/90000 \r\n";
        std::cout<<sdp<<std::endl;
        auto tmpsdp = parser(sdp);

        std::cout<<tmpsdp.mediaDescriptions[0].media.media<<std::endl;
    }
   
    
    


#endif












