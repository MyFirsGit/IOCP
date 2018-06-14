#include <WinSock2.h>
#include <stdio.h>
#include <Windows.h>
#include <string>
#include "CTcpClient.h"
#include <iostream>
using namespace std;
#pragma comment(lib, "ws2_32.lib")
#define MAX_THREAD		1000
#define MAX_BUF_SIZE	1024
//SOCKET sockClient;
int thread_num = 0;
CRITICAL_SECTION cs;
//DWORD WINAPI WorkThread(LPVOID tmp)
//{
//	EnterCriticalSection(&cs);
//	SYSTEMTIME time;
//	char  timebuf[256];
//
//	SOCKET 	sockClient = socket(AF_INET, SOCK_STREAM, 0);
//	const char chOpt=1;   
//	int   nErr=setsockopt(   sockClient,   IPPROTO_TCP,   TCP_NODELAY,   &chOpt,   sizeof(char));   
//	WSADATA wsaData;
//	char buf[1024] = {0};
//
//	SOCKADDR_IN addrSrv;
//	addrSrv.sin_family = AF_INET;
//	addrSrv.sin_port = htons(6000);
//	addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
//
//	if (SOCKET_ERROR == sockClient)
//	{
//		printf("Socket() error:%d",WSAGetLastError());
//		return 0;
//	}
//	if (connect(sockClient,(struct sockaddr*)&addrSrv, sizeof(addrSrv)) == INVALID_SOCKET)
//	{
//		printf("Connect failed%d:%d\r\n",thread_num,WSAGetLastError());
//		return 0;
//	}
//	else{
//		//recv(sockClient, buf, sizeof(buf), 0);
//		//printf("%s\n",buf);
//	}
//	int id = thread_num;
//	char buf1[MAX_BUF_SIZE] = {0};
//	char buf2[MAX_BUF_SIZE] = {0};
//	char buf3[MAX_BUF_SIZE] = {0};
//
//	sprintf(buf1,"这是第[%d]客户端发给服务器的第一条消息",id);
//	send(sockClient,buf1,sizeof(buf1),0);
//	GetLocalTime(&time);
//	sprintf(timebuf, "%02d/%02d/%02d %02d:%02d:%02d.%03d", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);
//	sprintf(buf1,"[%s]这是第[%d]客户端发给服务器的第一条消息",timebuf,id);
//	printf("%s\r\n",buf1);
//
//	sprintf(buf2,"这是第[%d]客户端发给服务器的第二条消息",id);
//	send(sockClient,buf2,sizeof(buf2),0);
//	GetLocalTime(&time);
//	sprintf(timebuf, "%02d/%02d/%02d %02d:%02d:%02d.%03d", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);
//	sprintf(buf2,"[%s]这是第[%d]客户端发给服务器的第二条消息",timebuf,id);
//	printf("%s\r\n",buf2);
//
//	Sleep(200);
//	sprintf(buf3,"这是第[%d]客户端发给服务器的第三条消息",id);
//	send(sockClient,buf3,sizeof(buf3),0);
//	GetLocalTime(&time);
//	sprintf(timebuf, "%02d/%02d/%02d %02d:%02d:%02d.%03d", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);
//	sprintf(buf3,"[%s]这是第[%d]客户端发给服务器的第三条消息",timebuf,id);
//	printf("%s\r\n",buf3);
//
//	closesocket(sockClient);
//	thread_num++;
//	LeaveCriticalSection(&cs);
//	return 0;
//}
DWORD WINAPI WorkThread(LPVOID tmp)
{
	ThreadParam* param = (ThreadParam*)tmp;
	bool bRet = param->client.Connect(param->ip.c_str(), param->port);
	if (!bRet)
	{
		return 0;
	}
	for (param->times=0; param->times < param->cycle; param->times++)
	{
		bRet = param->client.SendData();
		if (!bRet)
		{
			printf("【%d】发送失败", param->index);
			return false;
		}
		Sleep(param->sleepTime);
	}
	param->client.CloseSocket();
}
inline void keep_window_open()
{
	char ch;
	cin >> ch;
}
void main()
{
	InitializeCriticalSection(&cs);
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2,2),&wsaData) != 0)
	{
		printf("Failed to load winsock");
		return;
	}
	HANDLE *phThread = new HANDLE[MAX_THREAD];
	DWORD nthreadID;
	char  timebuf[256];
	SYSTEMTIME time;

	char sIp[] = "127.0.0.1";
	short port = 6000;
	for (int n= 0; n < MAX_THREAD;n++)
	{
		//sockClient	 = socket(AF_INET, SOCK_STREAM, 0);
		//const char chOpt=1;   
		//int   nErr=setsockopt(   sockClient,   IPPROTO_TCP,   TCP_NODELAY,   &chOpt,   sizeof(char));   
		//WSADATA wsaData;
		//char buf[1024] = {0};

		//SOCKADDR_IN addrSrv;
		//addrSrv.sin_family = AF_INET;
		//addrSrv.sin_port = htons(6000);
		//addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

		//if (SOCKET_ERROR == sockClient)
		//{
		//	printf("Socket() error:%d",WSAGetLastError());
		//	return ;
		//}
		//if (connect(sockClient,(struct sockaddr*)&addrSrv, sizeof(addrSrv)) == INVALID_SOCKET)
		//{
		//	printf("Connect failed%d:%d\r\n",thread_num,WSAGetLastError());
		//	return ;
		//}
		//else{
		//	//recv(sockClient, buf, sizeof(buf), 0);
		//	//printf("%s\n",buf);
		//}
		//int id = thread_num;
		//char buf1[MAX_BUF_SIZE] = {0};
		//char buf2[MAX_BUF_SIZE] = {0};
		//char buf3[MAX_BUF_SIZE] = {0};

		//sprintf(buf1,"这是第[%d]客户端发给服务器的第一条消息",id);
		//send(sockClient,buf1,sizeof(buf1),0);
		//GetLocalTime(&time);
		//sprintf(timebuf, "%02d/%02d/%02d %02d:%02d:%02d.%03d", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);
		//sprintf(buf1,"[%s]这是第[%d]客户端发给服务器的第一条消息",timebuf,id);
		//printf("%s\r\n",buf1);

		//sprintf(buf2,"这是第[%d]客户端发给服务器的第二条消息",id);
		//send(sockClient,buf2,sizeof(buf2),0);
		//GetLocalTime(&time);
		//sprintf(timebuf, "%02d/%02d/%02d %02d:%02d:%02d.%03d", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);
		//sprintf(buf2,"[%s]这是第[%d]客户端发给服务器的第二条消息",timebuf,id);
		//printf("%s\r\n",buf2);

		//Sleep(200);
		//sprintf(buf3,"这是第[%d]客户端发给服务器的第三条消息",id);
		//send(sockClient,buf3,sizeof(buf3),0);
		//GetLocalTime(&time);
		//sprintf(timebuf, "%02d/%02d/%02d %02d:%02d:%02d.%03d", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);
		//sprintf(buf3,"[%s]这是第[%d]客户端发给服务器的第三条消息",timebuf,id);
		//printf("%s\r\n",buf3);

		//closesocket(sockClient);
		//thread_num++;
		ThreadParam* param = new ThreadParam;
		param->client.SetParam(param);
		param->index = n;
		param->ip = sIp;
		param->port = port;
		param->cycle = 3;
		param->sleepTime = 200;
		phThread[n] = CreateThread(NULL,0,WorkThread,param,0,&param->threadid);
		::SetThreadPriority(phThread[n],THREAD_PRIORITY_BELOW_NORMAL);
	}
	//for (int n= 0; n < MAX_THREAD;n++)
	//{
	//	ResumeThread(phThread[n]);
	//}
	//for (int n= 0; n < MAX_THREAD;n++)
	//{
	//	CloseHandle(phThread[n]);
	//}

	keep_window_open();
	WSACleanup();

	DeleteCriticalSection(&cs);
}
