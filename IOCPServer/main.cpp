#include "IOCPServer.h"
#include <iostream>
#include <atltime.h>
using namespace std;

CIOCPServer* pIOCP;

void CALLBACK NotifyProc(LPVOID lparam, PER_IO_CONTEXT* pIoContext, UINT uFlag)
{
	char  timebuf[256];
	SYSTEMTIME time;

	switch (uFlag)
	{
	case NC_CLIENT_CONNECT:
	{
		GetLocalTime(&time);
		sprintf(timebuf, "%02d/%02d/%02d %02d:%02d:%02d.%03d", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);

		//cout << "[" << inet_ntoa(pIoContext->m_addr.sin_addr) << "-" << htons(pIoContext->m_addr.sin_port)
		//	<< "]->���ӣ�\r\n��һ�����ݡ�" << pIoContext->m_szBuf << "��\r\n" << endl;
		printf("[%s][%s-%d]->���ӣ���һ�����ݡ�%s��\r\n", timebuf,inet_ntoa(pIoContext->m_addr.sin_addr), htons(pIoContext->m_addr.sin_port), pIoContext->m_szBuf);
		break;
	}
	case NC_CLIENT_DISCONNECT:
	{
		cout << "[" << inet_ntoa(pIoContext->m_addr.sin_addr) << "-" << htons(pIoContext->m_addr.sin_port)
			<< "]->�Ͽ�����" << endl;
		break;
	}
	case NC_TRANSMIT:
	{
		cout << "[" << inet_ntoa(pIoContext->m_addr.sin_addr) << "-" << htons(pIoContext->m_addr.sin_port)
			<< "]->���ݷ��ͳɹ���" << pIoContext->m_szBuf << "��" << endl;
		break;
	}
	case NC_RECEIVE:
	{
		cout << "���յ�[" << inet_ntoa(pIoContext->m_addr.sin_addr) << "-" << htons(pIoContext->m_addr.sin_port)
			<< "]->��" << pIoContext->m_szBuf << "��" << endl;
		//// �յ���Ͷ��һ���첽����
		//PER_IO_CONTEXT* pSendIoContext = pIOCP->AllocateClientIOContext();
		//pSendIoContext->m_sock = pIoContext->m_sock;
		//pSendIoContext->m_addr = pIoContext->m_addr;
		//char szSend[] = "�����յ��������";
		//memcpy(pSendIoContext->m_szBuf, szSend, strlen(szSend));
		//pSendIoContext->m_dwBytesSend = strlen(szSend);
		//pIOCP->PostSend(pSendIoContext);
		break;
	}
	case NC_RECEIVE_COMPLETE:
		break;
	default:
		break;
	}
	return;
}

int main()
{
	pIOCP = new CIOCPServer;
	pIOCP->StartIOCP(NotifyProc, 6000);
	char szIn[32];
	while (1)
	{
		printf( "���� quit �˳�IOCP������: \n");
		memset(szIn, 0, sizeof(szIn));
		scanf_s("%s", szIn, 32);
		if (strcmp(szIn,"quit") == 0)
		{
			pIOCP->Stop();
			break;
		}
	}

	return 0;
}