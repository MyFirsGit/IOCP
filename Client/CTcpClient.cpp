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
	char sBuff[] = "��������������Ϣ";
	int nLeft = strlen(sBuff);
	int nSendLen = 0;
	char* sSendBuf = sBuff;
	while (nLeft > 0)
	{
		nSendLen = send(m_sock, sSendBuf, nLeft, 0);
		if (nSendLen == SOCKET_ERROR)
		{
			printf("[%d]��������ʧ��\r\n",m_param->index);
			return false;
		}
		nLeft -= nSendLen;
		(sSendBuf) += nSendLen;
	}
	printf("[%d]�̳߳ɹ�������������Ϣ\r\n",m_param->index);
}
bool CTcpClient::CloseSocket()
{
	closesocket(m_sock);
	printf("[%d]�ͻ��˲�����ϣ��ѹرա�\r\n",m_param->index);
	return true;
}
