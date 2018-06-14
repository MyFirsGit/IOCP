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
	int index;		//�߳����
	int times;
	DWORD threadid;	//�߳�id
	int cycle;		//ѭ������
	int sleepTime;	//����ʱ��
	CTcpClient client;
};
