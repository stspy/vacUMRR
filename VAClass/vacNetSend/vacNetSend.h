/**
 * @file vacNetSend.h
 * @brief
 * 定义接收数据类和发送数据类
 *
 * @see vacNetSend
 *
 * @author N. W. J. 
 * @version 0.1.0
 * @date 2014/02/26
 */

#ifndef __VACNETSEND_H
#define __VACNETSEND_H

#include <WinSock2.h>
#include <Windows.h>
#include <string>  
#include <iostream>  
#include <math.h> 
#include <fstream>
#include <sstream>
#include <vector>
#include "json.h"
#include "vacParser.h"
#include "vacRadarCommon.h"

using namespace std;

///接收缓存，临时存放数据，单位：字节
#define  BUFFER_DATA_SIZE 1024*10

///每一次接收数据大小，单位：字节
#define  ONCE_RECEIVE_DATA 1024

///解析后发送给客户端的数据缓存区，单位：字节
#define SEND_BUFFER_LEN 1024*10

///尝试连接服务器最多次数
#define TRY_MAX_TIME 5

///每次尝试连接服务器失败后等待时间，单位：毫秒
#define WAIT_SERVER_TIME 3000

/** 
 * @class vacRecNetData
 * @brief 接收雷达传过来的数据类，通信方式TCP 
 * 
 *
 * @ingroup vacRecNetData
 */
class vacRecNetData
{
public:
	///
	vacRecNetData();
	virtual~vacRecNetData();
	
	///转换数据格式
	void ChangeNetData();

	///配置接收数据IP和端口
	void GetRecAddr(std::string Addr) { m_sRecAddr = Addr;}
	void GetRecPort(unsigned int Port) {m_nRecPort = Port;}
	
	///配置本地IP和端口
	void GetSelfAddr(std::string Addr) {m_sSelfAddr = Addr;}
	void GetSelfPort(unsigned int Port) {m_nSelfPort = Port;}

	///配置数据库
	void GetHost(std::string Host) {m_sHost = Host;}
	void GetUser(std::string User) {m_sUser = User;}
	void GetPasswd(std::string Passwd) {m_sPasswd = Passwd;}
	void GetDBname(std::string DBname) {m_sDBname = DBname;}
	void GetDBport(unsigned int DBport) {m_nDBport = DBport;}
	///初始化TCP
	int InitTcp_rec();

	///连接服务器
	int ConnectServer();

	///接收数据
	int RecData();

	///停止接收数据
	void StopRecData();

	///解析函数
	int Translate();

	///初始化TCP
	int InitTcp_send();

	///接收客户端请求
	int AcceptClient();

	///发送数据
	int SendData();

	///停止发送数据
	void StopSendData();
	///
	std::string BackInfo(){return m_sPrintTmp;}

private:
	///加载套接字库
	WORD m_wVersionRequested;
	WSAData m_wsaData;

	///接收时用的套接字
	SOCKET m_SockRec;

	///服务器地址
	SOCKADDR_IN m_SeverAddr;

	///自身地址
	SOCKADDR_IN m_FromSever;

	///服务器端的IP和端口号
	std::string m_sRecAddr;
	 INT32U m_nRecPort;

	 ///发送时用的套接字
	 SOCKET m_SockSend;

	 ///接收来自客户端的套接字
	 SOCKET m_SockClient;

	 ///客户端网络地址
	 SOCKADDR_IN m_ClientAddr;

	 ///自身网络地址
	 SOCKADDR_IN m_SelfAddr;

	 ///自身IP和端口号
	 std::string m_sSelfAddr;
	 INT32U m_nSelfPort;

	 ///缓存大小
	 INT32U m_nBuffer;

	 ///接收数据大小
	 INT32U m_nStr_leng;

	 ///发送数据大小
	 int m_nSend_byte;

	///临时接收数据缓冲区
	char *m_pRecBuffer;

	///确认接收数据缓冲区
	char *m_pRecResult;

	///发送缓冲区
	char *m_pSendBuffer;

	///接收数据大小
	 int m_nRec_byte;	

	 ///提示信息
	std::string m_sPrintTmp;

	///用于存放网络数据的容器
	vector<INT8U> m_vec;


	///Json类的数据，string格式
	std::string m_sSend_Data;

	//写Json的两种方式
	Json::StyledWriter styled_writer;
	Json::FastWriter fast_writer;

	//写成Json对象
	Json::Value JsonTmp;

	///数据库信息
	std::string m_sHost;
	std::string m_sUser;
	std::string m_sPasswd;
	std::string m_sDBname;
	unsigned int m_nDBport;

	///初始化数据库和解析标志位
	int flag_init;

	///解析数据的对象
	vacDataParser  DataParser;

};



#endif