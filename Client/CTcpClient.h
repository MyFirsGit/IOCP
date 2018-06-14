#pragma once
#include <string>
#include <WinSock2.h>

struct ThreadParam;

class CTcpClient
{
public:
	CTcpClient();
	~CTcpClient();

	void SetParam(ThreadParam* param);
	bool Connect(const char* ip,short port);
	bool SendData();
	bool CloseSocket();
private:
	SOCKET m_sock;
	ThreadParam* m_param;
};


struct ThreadParam
{
	std::string ip;
	short port;
	int index;		//线程序号
	int times;
	DWORD threadid;	//线程id
	int cycle;		//循环次数
	int sleepTime;	//休眠时间
	CTcpClient client;
};
