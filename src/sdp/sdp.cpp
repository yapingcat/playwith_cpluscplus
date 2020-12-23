#include "sdp.h"
#include "StringUtil.h"


void Origin::parser(const std::string& orgin)
{
    std::string::size_type pos = 0;
    auto takeString = [&]() -> std::string {

        std::string value = "";
        auto pos1 = orgin.find(pos,' ');
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
        auto pos1 = orgin.find(pos,' ');
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
    nettype             = takeString();
    addrtype            = takeString();
    connection_address  = takeString();
}

void BandWidth::parser(const std::string& bandWidth)
{
    std::string::size_type pos = 0;
    auto takeString = [&]() -> std::string {

        std::string value = "";
        auto pos1 = orgin.find(pos,' ');
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

    bwtype    =  takeString();
    bandwidth =  takeString();
}

void Timing::parser(const std::string& timing)
{
    std::string::size_type pos = 0;
    auto takeString = [&]() -> std::string {

        std::string value = "";
        auto pos1 = orgin.find(pos,' ');
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

    start_time  =  takeString();
    stop_time   =  takeString();
}

void RepeatTimes::parser(const std::string& timing)
{
    std::string::size_type pos = 0;
    auto takeString = [&]() -> std::string {

        std::string value = "";
        auto pos1 = orgin.find(pos,' ');
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

    repeat_interval         =  takeString();
    active_duration         =  takeString();
    offsets_from_start_time =  takeString();
}

void TimeZones::parser(const std::string& timeZones)
{
    std::string::size_type pos = 0;
    auto takeString = [&]() -> std::string {

        std::string value = "";
        auto pos1 = orgin.find(pos,' ');
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
    while(pos != orgin.size())
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

void Media::parser(const std::string& media)
{
    std::string::size_type pos = 0;
    auto takeString = [&]() -> std::string {

        std::string value = "";
        auto pos1 = orgin.find(pos,' ');
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

    media                = takeString();
    std::string ports    = takeString();
    proto                = takeString();
    std::string fmtLists = takeString();
    
    if(ports.find("/") != std::string::npos)
    {
        int pn = std::stoi(ports.substr(ports.find("/") + 1));
        
    }
    else
    {
        ports.push_back(std::stoi(ports));
    }
    
}

void Attribute::parser(const std::string& attr)
{
    splitInTwoPart(attr,":",name,value);
}


void Control::decodeValue(const std::string& value)
{
    auto pos = value.find(":");
    if(pos != std::string::npos)
    {
        url = value.substr(pos + 1);
    }
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

    readLines(sdp,[&tmpSdp](const char* sdp,size_t len){
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
}

#ifdef SDP_TEST

    int main()
    {
        std::string sdp =  "v=0\r\n
                        o=alice 2890844526 2890844526 IN IP4 host.anywhere.com\r\n
                        s=Rtc Server\r\n
                        c=IN IP4 host.anywhere.com\r\n
                        t=0 0\r\n
                        m=audio 49170 RTP/AVP 0\r\n
                        a=rtpmap:0 PCMU/8000\r\n
                        m=video 51372 RTP/AVP 31\r\n
                        a=rtpmap:31 H261/90000\r\n
                        m=video 53000 RTP/AVP 32\r\n
                        a=rtpmap:32 MPV/90000 \r\n";

        auto tmpsdp = parser(sdp);

        std::cout<<tmpsdp.MediaDescription[0].media.media<<std::endl;
    }
   
    
    


#endif












