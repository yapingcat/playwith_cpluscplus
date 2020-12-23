#ifndef SOCKET_API_H
#define SOCKET_API_H

class SocketApi
{
public:
	static int createTcpSocket();
	static int createServerSocket(const std::string& ip, uint16_t port);
	static int acceptClient(int server,std::string& ip, uint16_t& port);
	static int acceptClient(int server);
	static int listen(int sc,int backlog);
	static int bind(int sc,const std::string& ip, uint16_t port);
	static int connect(int sc,const std::string& ip,uint16_t port);
	static int setReuseOption(int sc);
	static int setBlock(int sc,int block);
	static int setSocketOption(int sc,int level,int option,int value);
	static int getSocketOption(int sc,int level,int option,int& value);
	static int close(int sc);
    static int getPeerName(int sc, std::string& ip,uint16_t& port);
};




#endif