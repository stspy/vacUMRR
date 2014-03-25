/**
 * @file vacNetRec.h
 * @brief
 * 定义接收数据类
 *
 * @see vacNetRec
 *
 * @author N. W. J.
 * @version 0.1.0
 * @date 2014/02/26
 */

#ifndef __VACNETREC_H
#define __VACNETREC_H
#include <iostream>  
#include <math.h> 
#include <fstream>
#include <sstream>
#include <WinSock2.h>
#include <Windows.h>
#include <string>  
#include "json.h"
#include "vacRadarCommon.h"

using namespace std;

///接收缓存，临时存放数据，单位：字节
#define  BUFFER_DATA_SIZE 1024*10

///接收缓存区大小，单位：字节
#define REC_BUFFER_LEN 1024*10

///尝试连接服务器最多次数
#define TRY_MAX_TIME 10

///每次尝试连接服务器失败后等待时间，单位：毫秒
#define WAIT_SERVER_TIME 3000

/** 
 * @class ClientRec
 * @brief 接收经服务器解析后的数据类. 
 * 
 *
 * @ingroup ClientRec
 */

class ClientRec
{
public:
	///
	ClientRec();
	~ClientRec();

	///获取IP地址与端口
	void GetRecAddr(std::string Addr) { m_sRecAddr = Addr;}
	void GetRecPort(unsigned int Port) {m_nRecPort = Port;}

	///初始化Tcp
	int InitTcp();

	///连接服务器
	int ConnectServer();

	///接收数据
	int RecData();

	///接收的数据转换成Json Value
	char *PreTransDatatoJson();

	///停止接收
	void StopRecData();

	///显示接收数据
	void ShowRecData();

	///获取解析数据
	const char* GetAll();
	const char* GetFeature_Msg_1();
	const char* GetFeature_Msg_2();
	const char* GetInfo_Msg_1();
	const char* GetInfo_Msg_2();
	const char* GetObject_Data_1_Msg();
	const char* GetObject_Data_Ctrl_Msg();
	const char* GetPresence_Msg();
	const char* GetRelay_Ctrl_Msg();	
	const char* GetStatus_Msg();
	const char* GetTime_Msg();
	const char* GetTriggered_Obj_Msg();
	const char* GetWrong_Dir_Msg();

	///
	std::string BackInfo(){return m_sPrintTmp;}

private:
	///加载套接字库
	WORD m_wVersionRequested;
	WSAData m_wsaData;

	///接收时用的套接字
	SOCKET m_SockRec;

	///接收时用的网络地址
	SOCKADDR_IN m_SeverAddr;

	///服务器端的IP和端口号
	std::string m_sRecAddr;
	 INT32U m_nRecPort;
	
	 ///缓存大小
	 INT32U m_nBuffer;
	
	 ///接收缓冲区
	char *m_pRecBuffer;
	char *m_pRecResult;
	
	///接收数据大小
	 int m_nRec_byte;	
	std::string m_sPrintTmp;
	
	///Jason格式读
	Json::Reader m_jReader;
	Json::Value m_json_Object;

	///Json写
	Json::StyledWriter m_jStyled_writer;

	///Jason类中的Feature_Msg_1项
	Json::Value m_Feature_Msg_1;

	///Jason类中的Feature_Msg_2项
	Json::Value m_Feature_Msg_2;

	///Jason类中的Info_Msg_1项
	Json::Value m_Info_Msg_1;

	///Jason类中的Info_Msg_2项
	Json::Value m_Info_Msg_2;

	///Jason类中的Object_Data_1_Msg项
	Json::Value m_Object_Data_1_Msg;

	///Jason类中的Object_Data_Ctrl_Msg项
	Json::Value m_Object_Data_Ctrl_Msg;

	///Jason类中的Presence_Msg项
	Json::Value m_Presence_Msg;

	///Jason类中的Relay_Ctrl_Msg项
	Json::Value m_Relay_Ctrl_Msg;	

	///Jason类中的Status_Msg项
	Json::Value m_Status_Msg;

	///Jason类中的Time_Msg项
	Json::Value m_Time_Msg;

	///Jason类中的Triggered_Obj_Msg项
	Json::Value m_Triggered_Obj_Msg;

	///Jason类中的Wrong_Dir_Msg项
	Json::Value m_Wrong_Dir_Msg;
};

#endif