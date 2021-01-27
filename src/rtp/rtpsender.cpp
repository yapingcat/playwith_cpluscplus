//
// blocking_udp_echo_client.cpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2019 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <thread>
#include "asio.hpp"
#include "RtpPacket.h"

using asio::ip::udp;

enum { max_length = 1024 };

int main(int argc, char* argv[])
{
  try
  {
    if (argc != 3)
    {
      std::cerr << "Usage: rtpsender <host> <port>\n";
      return 1;
    }

    asio::io_context io_context;

    udp::socket s(io_context, udp::endpoint(udp::v4(), 0));

    udp::resolver resolver(io_context);
    udp::resolver::results_type endpoints =
      resolver.resolve(udp::v4(), argv[1], argv[2]);
    
    uint16_t seq = 0;
    uint32_t tm = 0;
    for(;;)
    {
        RtpPacket pkg;
        pkg.version = 2;
        pkg.padding = 0;
        pkg.pt = 96;
        pkg.sequence = seq++;
        pkg.timeStamp = tm;
        pkg.ssrc = 0x12345678;
        tm += 40;
        pkg.payload.resize(1000,1);
        auto rtp = endcode(pkg);
        s.send_to(asio::buffer(rtp), *endpoints.begin());

        std::this_thread::sleep_for(std::chrono::milliseconds(40));

    }

  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}
