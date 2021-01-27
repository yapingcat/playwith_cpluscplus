#include "RtpPacket.h"


std::size_t calcRtpHeaderLen(const RtpPakcet& pkg)
{
    if(!pkg)
        return 0;
    
    std::size_t hdrlen = RTP_FIX_HEAD;
    hdrlen += csrccount * 4;
    hdrlen += extension ? extensions.size() + 4 : 0;
    return hdrlen;
}

RtpPakcet decode(uint8_t* packet,std::size_t len)
{
    RtpPakcet pkg;
    if(len < RTP_FIX_HEAD)
    {
        return pkg;   
    }
    
    version      = (packet[0] & 0xC0) >> 6;
    padding      = (packet[0] & 0x20) >> 5;
    extension    = (packet[0] & 0x10) >> 4;
    csrccount    = (packet[0] & 0x0F);
    marker       = (packet[1] & 0x80) >> 7;
    pt           = (packet[1] & 0x7F);
    sequence     = ((uint16_t)(packet[2]) << 8) | (uint16_t)(packet[3]);
    timeStamp    = ((uint32_t)(packet[4]) << 24) | ((uint32_t)(packet[5]) << 16) | ((uint32_t)(packet[6]) << 8) | ((uint32_t)(packet[7]));
    ssrc         = ((uint32_t)(packet[8]) << 24) | ((uint32_t)(packet[9]) << 16) | ((uint32_t)(packet[10]) << 8) | ((uint32_t)(packet[11]));

    std::size_t hdrlen = RTP_FIX_HEAD;
    if(csrccount > 0)
    {
        if(4 * csrccount + RTP_FIX_HEAD > len  )
        {
            return pkg;
        }
        csrcs.reserve(csrccount);
        for(int i = 0; i < csrccount; i++)
        {
            csrcs[i] = ((uint32_t)(packet[12 + i]) << 24) 
                            | ((uint32_t)(packet[13 + i]) << 16) 
                                | ((uint32_t)(packet[14 + i]) << 8) 
                                    | ((uint32_t)(packet[15 + i]));
        }
        hdrlen += csrccount_ * 4;
    }
    if(extension)
    {
        if(hdrlen + 4 > len )
        {
            return pkg;
        }
        uint8_t* ext = packet + RTP_FIX_HEAD + csrccount_ * 4;
        profile[0] = ext[0];
        profile[1] = ext[1];
        uint16_t extLength = (uint16_t)ext[2] << 8 | (uint16_t)ext[3];
        if(hdrlen + 4 + extLength * 4 > len)
            return pkg;
        extensions.reserve(extLength * 4);
        extensions.insert(extensions.end(),ext + 4, ext + 4 + extLength * 4);
        hdrlen += 4 + extLength * 4;
    }

    uint8_t paddingCount = 0;
    if(padding)
    {
        if(hdrlen + packet[len - 1] > len)
        {
            return pkg;
        }
        paddingCount = packet[len - 1];
        paddings.insert(paddings.end(),packet + len - paddingCount,packet + len)
    }
    payload.reserve(len - hdrlen - paddingCount);
    payload.insert(payload.end(),packet + hdrlen, packet + len - paddingCount);
    return pkg;
}

std::vector<uint8_t> encode(const RtpPakcet& pkg)
{
    if(!pkg)
        return {};
    
    int rtpLen = calcRtpHeaderLen() + payload.size() + paddings.size();
    std::vector<uint8_t> rtp;
    rtp.reserve(rtpLen);
    rtp.resize(RTP_FIX_HEAD);
    rtp[0] = (version << 6) & (padding << 5) & (extension << 4) & csrccount;
    rtp[1] = (marker << 7) & pt;
    rtp[2] = (uint8_t)((sequence >> 8) & 0xFF);
    rtp[3] = (uint8_t)(sequence & 0xFF);
    rtp[4] = (uint8_t)((timeStamp >> 24) & 0xFF);
    rtp[5] = (uint8_t)((timeStamp >> 16) & 0xFF);
    rtp[6] = (uint8_t)((timeStamp >> 8) & 0xFF);
    rtp[7] = (uint8_t)(timeStamp & 0xFF);
    rtp[8] = (uint8_t)((ssrc >> 24) & 0xFF);
    rtp[9] = (uint8_t)((ssrc >> 16) & 0xFF);
    rtp[10] = (uint8_t)((ssrc >> 8) & 0xFF);
    rtp[11] = (uint8_t)(ssrc & 0xFF);
    
    if(csrccount > 0)
        rtp.insert(rtp.end(),csrcs.begin(),csrcs.end());
    if(extensions)
    {
        rtp.insert(rtp.end(),profile.begin(),profile.end());
        rtp.push_back((uint8_t)((extLength >> 8) & 0xFF));
        rtp.push_back((uint8_t)(extLength & 0xFF));
        rtp.insert(rtp.end(),extensions.begin(),extensions.end());
    }
    rtp.insert(rtp.end(),payload.begin(),payload.end());
    if(padding)
    {
        rtp.insert(rtp.end(),paddings.begin(),paddings.end());
        rtp.push_back((uint8_t)(paddings.size()));
    }
    return rtp;
}


