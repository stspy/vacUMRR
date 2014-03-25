/**
 * @file vacNetSend.h
 * @brief
 * �������������ͷ���������
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

///���ջ��棬��ʱ������ݣ���λ���ֽ�
#define  BUFFER_DATA_SIZE 1024*10

///ÿһ�ν������ݴ�С����λ���ֽ�
#define  ONCE_RECEIVE_DATA 1024

///�������͸��ͻ��˵����ݻ���������λ���ֽ�
#define SEND_BUFFER_LEN 1024*10

///�������ӷ�����������
#define TRY_MAX_TIME 5

///ÿ�γ������ӷ�����ʧ�ܺ�ȴ�ʱ�䣬��λ������
#define WAIT_SERVER_TIME 3000

/** 
 * @class vacRecNetData
 * @brief �����״ﴫ�����������࣬ͨ�ŷ�ʽTCP 
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
	
	///ת�����ݸ�ʽ
	void ChangeNetData();

	///���ý�������IP�Ͷ˿�
	void GetRecAddr(std::string Addr) { m_sRecAddr = Addr;}
	void GetRecPort(unsigned int Port) {m_nRecPort = Port;}
	
	///���ñ���IP�Ͷ˿�
	void GetSelfAddr(std::string Addr) {m_sSelfAddr = Addr;}
	void GetSelfPort(unsigned int Port) {m_nSelfPort = Port;}

	///�������ݿ�
	void GetHost(std::string Host) {m_sHost = Host;}
	void GetUser(std::string User) {m_sUser = User;}
	void GetPasswd(std::string Passwd) {m_sPasswd = Passwd;}
	void GetDBname(std::string DBname) {m_sDBname = DBname;}
	void GetDBport(unsigned int DBport) {m_nDBport = DBport;}
	///��ʼ��TCP
	int InitTcp_rec();

	///���ӷ�����
	int ConnectServer();

	///��������
	int RecData();

	///ֹͣ��������
	void StopRecData();

	///��������
	int Translate();

	///��ʼ��TCP
	int InitTcp_send();

	///���տͻ�������
	int AcceptClient();

	///��������
	int SendData();

	///ֹͣ��������
	void StopSendData();
	///
	std::string BackInfo(){return m_sPrintTmp;}

private:
	///�����׽��ֿ�
	WORD m_wVersionRequested;
	WSAData m_wsaData;

	///����ʱ�õ��׽���
	SOCKET m_SockRec;

	///��������ַ
	SOCKADDR_IN m_SeverAddr;

	///�����ַ
	SOCKADDR_IN m_FromSever;

	///�������˵�IP�Ͷ˿ں�
	std::string m_sRecAddr;
	 INT32U m_nRecPort;

	 ///����ʱ�õ��׽���
	 SOCKET m_SockSend;

	 ///�������Կͻ��˵��׽���
	 SOCKET m_SockClient;

	 ///�ͻ��������ַ
	 SOCKADDR_IN m_ClientAddr;

	 ///���������ַ
	 SOCKADDR_IN m_SelfAddr;

	 ///����IP�Ͷ˿ں�
	 std::string m_sSelfAddr;
	 INT32U m_nSelfPort;

	 ///�����С
	 INT32U m_nBuffer;

	 ///�������ݴ�С
	 INT32U m_nStr_leng;

	 ///�������ݴ�С
	 int m_nSend_byte;

	///��ʱ�������ݻ�����
	char *m_pRecBuffer;

	///ȷ�Ͻ������ݻ�����
	char *m_pRecResult;

	///���ͻ�����
	char *m_pSendBuffer;

	///�������ݴ�С
	 int m_nRec_byte;	

	 ///��ʾ��Ϣ
	std::string m_sPrintTmp;

	///���ڴ���������ݵ�����
	vector<INT8U> m_vec;


	///Json������ݣ�string��ʽ
	std::string m_sSend_Data;

	//дJson�����ַ�ʽ
	Json::StyledWriter styled_writer;
	Json::FastWriter fast_writer;

	//д��Json����
	Json::Value JsonTmp;

	///���ݿ���Ϣ
	std::string m_sHost;
	std::string m_sUser;
	std::string m_sPasswd;
	std::string m_sDBname;
	unsigned int m_nDBport;

	///��ʼ�����ݿ�ͽ�����־λ
	int flag_init;

	///�������ݵĶ���
	vacDataParser  DataParser;

};



#endif