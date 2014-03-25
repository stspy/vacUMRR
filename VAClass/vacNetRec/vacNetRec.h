/**
 * @file vacNetRec.h
 * @brief
 * �������������
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

///���ջ��棬��ʱ������ݣ���λ���ֽ�
#define  BUFFER_DATA_SIZE 1024*10

///���ջ�������С����λ���ֽ�
#define REC_BUFFER_LEN 1024*10

///�������ӷ�����������
#define TRY_MAX_TIME 10

///ÿ�γ������ӷ�����ʧ�ܺ�ȴ�ʱ�䣬��λ������
#define WAIT_SERVER_TIME 3000

/** 
 * @class ClientRec
 * @brief ���վ��������������������. 
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

	///��ȡIP��ַ��˿�
	void GetRecAddr(std::string Addr) { m_sRecAddr = Addr;}
	void GetRecPort(unsigned int Port) {m_nRecPort = Port;}

	///��ʼ��Tcp
	int InitTcp();

	///���ӷ�����
	int ConnectServer();

	///��������
	int RecData();

	///���յ�����ת����Json Value
	char *PreTransDatatoJson();

	///ֹͣ����
	void StopRecData();

	///��ʾ��������
	void ShowRecData();

	///��ȡ��������
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
	///�����׽��ֿ�
	WORD m_wVersionRequested;
	WSAData m_wsaData;

	///����ʱ�õ��׽���
	SOCKET m_SockRec;

	///����ʱ�õ������ַ
	SOCKADDR_IN m_SeverAddr;

	///�������˵�IP�Ͷ˿ں�
	std::string m_sRecAddr;
	 INT32U m_nRecPort;
	
	 ///�����С
	 INT32U m_nBuffer;
	
	 ///���ջ�����
	char *m_pRecBuffer;
	char *m_pRecResult;
	
	///�������ݴ�С
	 int m_nRec_byte;	
	std::string m_sPrintTmp;
	
	///Jason��ʽ��
	Json::Reader m_jReader;
	Json::Value m_json_Object;

	///Jsonд
	Json::StyledWriter m_jStyled_writer;

	///Jason���е�Feature_Msg_1��
	Json::Value m_Feature_Msg_1;

	///Jason���е�Feature_Msg_2��
	Json::Value m_Feature_Msg_2;

	///Jason���е�Info_Msg_1��
	Json::Value m_Info_Msg_1;

	///Jason���е�Info_Msg_2��
	Json::Value m_Info_Msg_2;

	///Jason���е�Object_Data_1_Msg��
	Json::Value m_Object_Data_1_Msg;

	///Jason���е�Object_Data_Ctrl_Msg��
	Json::Value m_Object_Data_Ctrl_Msg;

	///Jason���е�Presence_Msg��
	Json::Value m_Presence_Msg;

	///Jason���е�Relay_Ctrl_Msg��
	Json::Value m_Relay_Ctrl_Msg;	

	///Jason���е�Status_Msg��
	Json::Value m_Status_Msg;

	///Jason���е�Time_Msg��
	Json::Value m_Time_Msg;

	///Jason���е�Triggered_Obj_Msg��
	Json::Value m_Triggered_Obj_Msg;

	///Jason���е�Wrong_Dir_Msg��
	Json::Value m_Wrong_Dir_Msg;
};

#endif