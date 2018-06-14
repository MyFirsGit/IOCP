#include "CTcpClient.h"



CTcpClient::CTcpClient()
{
	m_sock = socket(AF_INET, SOCK_STREAM, 0);
	m_param = NULL;
}


CTcpClient::~CTcpClient()
{
	closesocket(m_sock);
	if (m_param)
	{
		delete m_param;
		m_param = NULL;
	}
}
void CTcpClient::SetParam(ThreadParam* param)
{
	m_param = param;
}
bool CTcpClient::Connect(const char* ip, short port)
{
	SOCKADDR_IN ServerAddr = { 0 };
	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_addr.s_addr = inet_addr(ip);
	ServerAddr.sin_port = htons(port);
	int nRet = connect(m_sock, (struct sockaddr*)&ServerAddr, sizeof(SOCKADDR_IN));
	if (nRet == SOCKET_ERROR)
	{
		return false;
	}
	return true;
}
bool CTcpClient::SendData()
{
	char sBuff[] = "发给服务器的消息";
	int nLeft = strlen(sBuff);
	int nSendLen = 0;
	char* sSendBuf = sBuff;
	while (nLeft > 0)
	{
		nSendLen = send(m_sock, sSendBuf, nLeft, 0);
		if (nSendLen == SOCKET_ERROR)
		{
			printf("[%d]发送数据失败\r\n",m_param->index);
			return false;
		}
		nLeft -= nSendLen;
		(sSendBuf) += nSendLen;
	}
	printf("[%d]线程成功发给服务器消息\r\n",m_param->index);
}
bool CTcpClient::CloseSocket()
{
	closesocket(m_sock);
	printf("[%d]客户端测试完毕，已关闭。\r\n",m_param->index);
	return true;
}
