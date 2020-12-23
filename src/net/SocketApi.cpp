#include "SocketApi.h"

#ifndef WIN32
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #include <fcntl.h>
    #include <sys/ioctl.h>
    #include <netinet/tcp.h>
#endif

int SocketApi::createTcpSocket()
{
	return ::socket(AF_INET,SOCK_STREAM,0);	
}

int SocketApi::createServerSocket(const std::string& ip, uint16_t port)
{
	int server = createTcpSocket();
    setBlock(server,0);
	setReuseOption(server);
	int ret = bind(server,ip,port);
	return ret == 0 ? server: -1;
}

int SocketApi::acceptClient(int server,std::string&ip, uint16_t& port)
{
	sockaddr_in sa;
   	socklen_t len = sizeof(sa);
	int sc = ::accept(server,(sockaddr*)&sa,&len);
    if( sc < 0)
    {
        return sc;
    }
    char addr[64]= {0};
    ::inet_ntop(AF_INET,&(sa.sin_addr),addr,63);
    ip = addr;
    port = ntohs(sa.sin_port);
    return sc;
}

int SocketApi::acceptClient(int server)
{
	sockaddr_in sa;
   	socklen_t len = sizeof(sa);
	int sc = ::accept(server,(sockaddr*)&sa,&len);
    if( sc < 0)
    {
        return sc;
    }
    return sc;
}

int SocketApi::listen(int sc,int backlog)
{
	return ::listen(sc,backlog);
}

int SocketApi::bind(int sc,const std::string& ip, uint16_t port)
{
	sockaddr_in sa;
    sa.sin_family = AF_INET;
    sa.sin_port = htons(port);
    inet_pton(AF_INET, ip == ""?"0.0.0.0":ip.c_str(),&sa.sin_addr);
    return ::bind(sc,(sockaddr*)&sa,sizeof(sa));
}

int SocketApi::connect(int sc, const std::string& ip,uint16_t port)
{
	sockaddr_in sa;
    sa.sin_family = AF_INET;
    sa.sin_port = htons(port);
    inet_pton(AF_INET,ip.c_str(),&sa.sin_addr);
    return ::connect(sc,(sockaddr*)&sa,sizeof(sa));	
}

int SocketApi::setReuseOption(int sc)
{
	char value = 1;
	int ret = setSocketOption(sc,SOL_SOCKET,SO_REUSEADDR,value);
	ret = setSocketOption(sc,SOL_SOCKET,SO_REUSEPORT,value);
	return ret;	
}

int SocketApi::setBlock(int sc,int block)
{
    int flags = ::fcntl(sc,F_GETFL);
    flags = flags & ~O_NONBLOCK;
    if(!block) flags = flags & O_NONBLOCK;
	return ::fcntl(sc,F_SETFL,flags);
}

int SocketApi::setSocketOption(int sc,int level,int option, int value)
{
	return ::setsockopt(sc,level,option, reinterpret_cast<const char*>(&value),sizeof(value));
}

int SocketApi::getSocketOption(int sc,int level,int option, int& value)
{
	socklen_t len = sizeof(value);
	return ::getsockopt(sc,level,option, reinterpret_cast<char*>(&value),&len);
}

int SocketApi::close(int sc)
{
	return ::close(sc);
}

int SocketApi::getPeerName(int sc, std::string& ip, uint16_t& port)
{
    sockaddr_in sa;
    socklen_t len = sizeof(sa);
    int ret = ::getpeername(sc,(sockaddr*)&sa,&len);
    if(ret != 0)
    {
        return ret;
    }

    char addr[64] = {0};
    ::inet_ntop(AF_INET,&(sa.sin_addr),addr,63);
    ip = addr;
    port = ntohs(sa.sin_port);
    return ret;
}