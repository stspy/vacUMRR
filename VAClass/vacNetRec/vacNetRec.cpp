/**
 * @file vacNetRec.cpp
 * @brief
 *	
 *
 * @see vacNetRec
 *
 * @author N. W. J.
 * @version 0.1.0
 * @date 2014/02/26
 */


/** include files **/
#include "vacNetRec.h"

/**
 * @brief ClientRec()
 *
 * 
 * @author N. W. J.
 * 
 * @param None. 
 *
 * @return None.
 */
ClientRec::ClientRec()
{
	//为缓冲区申请内存并初始化相关变量
	m_pRecBuffer = new char [REC_BUFFER_LEN ];
	m_pRecResult = new char [REC_BUFFER_LEN ];	
	m_nRec_byte = 0;

	//设置发送缓存
	m_nBuffer=BUFFER_DATA_SIZE;

}


/**
 * @brief InitTcp()
 *
 * 初始化网络套接字
 * @author N. W. J.
 * 
 * @param None. 
 *
 * @return 0：初始化完成 
.*	         其他：初始化错误
 */
int ClientRec::InitTcp()
{
	int err = 0;

	//加载套接字库
	m_wVersionRequested = MAKEWORD(1, 1);
	err = WSAStartup( m_wVersionRequested, &m_wsaData );
	if (err != 0)
	{
		m_sPrintTmp = "WSAStartup() failed!";
		cout<<m_sPrintTmp<<endl;
		return err;
	}
	if ( LOBYTE(m_wsaData.wVersion) != 1 ||HIBYTE(m_wsaData.wVersion) != 1 )
	{
		WSACleanup();
		m_sPrintTmp = "Invalid WinSock version!";
		cout<<m_sPrintTmp<<endl;
		return err;
	}

	//设置通信方式为TCP
	m_SockRec = socket(AF_INET, SOCK_STREAM, 0);
	if(m_SockRec == INVALID_SOCKET)
	{
		m_sPrintTmp = "Receive socket() failed !";
		cout<<m_sPrintTmp<<endl;
		return -1 ;
	}

	//接收数据时，服务器端的网络地址(即从该网络地址接收数据)
	m_SeverAddr.sin_family = AF_INET;
	m_SeverAddr.sin_addr.S_un.S_addr = inet_addr(m_sRecAddr.data());
	m_SeverAddr.sin_port = htons(m_nRecPort);
	
	//设置接收缓存区
	setsockopt(m_SockRec, SOL_SOCKET,SO_RCVBUF,(const char*)&m_nBuffer,sizeof(int));

	m_sPrintTmp = "\nTcp Receive Init() OK !";
	cout<<m_sPrintTmp<<endl;
	return 0;

}

/**
 * @brief ConnectServer()
 *
 * 建立与服务器连接
 * @author N. W. J.
 * 
 * @param None. 
 *
 * @return 0：连接成功
.*		  -1：连接失败
 */
int  ClientRec::ConnectServer()
{
	int i;

	//尝试多次与服务器建立连接
	for (i=0; i<TRY_MAX_TIME; i++)
	{
		if(connect(m_SockRec,(SOCKADDR*)&m_SeverAddr,
			sizeof(SOCKADDR))== -1) //与服务器建立连接
			cout<<"Try to Connect Server :  "<<i<<endl;
		else
			break;
		Sleep(WAIT_SERVER_TIME);
	}

	//多次尝试失败退出
	if (i >= TRY_MAX_TIME)
	{
		m_sPrintTmp = "Connect Server Failed !";
		cout<<m_sPrintTmp<<endl;
		return -1;
	}
	else
		m_sPrintTmp = "\nConnect Server OK ! Wait Sever Send Data ……\n";
	cout<<m_sPrintTmp<<endl;
	return 0;
}

/**
 * @brief RecData()
 *
 * 接收服务器发来的数据
 * @author N. W. J.
 * 
 * @param None. 
 *
 * @return 接收到的数据大小，单位：字节
 *		  -1：接收错误
 */
int ClientRec::RecData()
{
	//接收数据，阻塞当前程序，直到接收到数据
	m_nRec_byte = recv(m_SockRec, m_pRecBuffer, REC_BUFFER_LEN, 0);
	
	//接收数据有效
	if (m_nRec_byte > 0 && m_nRec_byte < REC_BUFFER_LEN)
	{
		cout<<"Receive "<<m_nRec_byte<<" byte"<<endl;
		return m_nRec_byte;
	}

	//接收数据无效
	else
	{
		cout<<"Receive Error !"<<endl;;
		return -1;
	}
}


/**
 * @brief StopRecData()
 *
 * 断开与服务器的连接，停止接收数据
 * @author N. W. J.
 * 
 * @param None. 
 *
 * @return None.
 */
void ClientRec::StopRecData()
{
	//关闭套接字
	closesocket(m_SockRec);
	WSACleanup();
	m_sPrintTmp = "Stop Connect Server !";
	cout<<m_sPrintTmp<<endl;
}

/**
 * @brief GetRecData()
 *
 * 返回接收到数据的指针
 * @author N. W. J.
 * 
 * @param None. 
 *
 * @return 数据指针m_pRecResult
  *		  NULL：Json解读失败
 */
char * ClientRec::PreTransDatatoJson()
{
	strncpy(m_pRecResult, m_pRecBuffer, m_nRec_byte);
	m_pRecResult[m_nRec_byte] = '\0';

	//Json 解读
	if (!m_jReader.parse(m_pRecResult, m_json_Object))
		return NULL;
	else
		return m_pRecResult;
}

/**
 * @brief ShowRecData()
 *
 * 在终端输出接收到的信息
 * @author N. W. J.
 * 
 * @param None. 
 *
 * @return None.
 */
void ClientRec::ShowRecData()
{
	//在终端输出接收到的数据
	cout<<m_pRecResult<<endl;

}

/**
 * @brief GetAll()
 *
 * 返回接收全部数据的指针
 * @author N. W. J.
 * 
 * @param None. 
 *
 * @return 数据指针m_pRecResult
  *		
 */
const char* ClientRec::GetAll()
{
	return m_pRecResult;
}

/**
 * @brief GetFeature_Msg_1()
 *
 * 返回接收GetFeature_Msg_1指针
 * @author N. W. J.
 * 
 * @param None. 
 *
 * @return GetFeature_Msg_1指针
  *		
 */
const char* ClientRec::GetFeature_Msg_1()
{
	m_Feature_Msg_1 = m_json_Object["Feature_Msg"][0u];
	m_sPrintTmp = m_jStyled_writer.write(m_Feature_Msg_1);
	cout<<m_sPrintTmp<<endl;
	return m_sPrintTmp.data();
}

/**
 * @brief GetFeature_Msg_2()
 *
 * 返回接收GetFeature_Msg_2指针
 * @author N. W. J.
 * 
 * @param None. 
 *
 * @return GetFeature_Msg_2指针
  *		
 */
const char* ClientRec::GetFeature_Msg_2()
{
	m_Feature_Msg_2 = m_json_Object["Feature_Msg"][1u];
	m_sPrintTmp = m_jStyled_writer.write(m_Feature_Msg_2);
	cout<<m_sPrintTmp<<endl;
	return m_sPrintTmp.data();
}

/**
 * @brief GetInfo_Msg_1()
 *
 * 返回接收GetInfo_Msg_1指针
 * @author N. W. J.
 * 
 * @param None. 
 *
 * @return GetInfo_Msg_1指针
  *		
 */
const char* ClientRec::GetInfo_Msg_1()
{
	m_Info_Msg_1 = m_json_Object["Info_Msg_1"];
	m_sPrintTmp = m_jStyled_writer.write(m_Info_Msg_1);
	cout<<m_sPrintTmp<<endl;
	return m_sPrintTmp.data();

}

/**
 * @brief GetInfo_Msg_2()
 *
 * 返回接收GetInfo_Msg_2指针
 * @author N. W. J.
 * 
 * @param None. 
 *
 * @return GetInfo_Msg_2指针
  *		
 */
const char* ClientRec::GetInfo_Msg_2()
{
	m_Info_Msg_2 = m_json_Object["Info_Msg_2"];
	m_sPrintTmp = m_jStyled_writer.write(m_Info_Msg_2);
	cout<<m_sPrintTmp<<endl;
	return m_sPrintTmp.data();

}

/**
 * @brief GetObject_Data_1_Ms()
 *
 * 返回接收GetObject_Data_1_Ms指针
 * @author N. W. J.
 * 
 * @param None. 
 *
 * @return GetObject_Data_1_Ms指针
  *		
 */
const char* ClientRec::GetObject_Data_1_Msg()
{
	m_Object_Data_1_Msg = m_json_Object["Object_Data_1_Msg"];
	m_sPrintTmp = m_jStyled_writer.write(m_Object_Data_1_Msg);
	cout<<m_sPrintTmp<<endl;
	return m_sPrintTmp.data();

}

/**
 * @brief GetObject_Data_Ctrl_Msg()
 *
 * 返回接收GetObject_Data_Ctrl_Msg指针
 * @author N. W. J.
 * 
 * @param None. 
 *
 * @return GetObject_Data_Ctrl_Msg指针
  *		
 */
const char* ClientRec::GetObject_Data_Ctrl_Msg()
{
	m_Object_Data_Ctrl_Msg = m_json_Object["Object_Data_Ctrl_Msg"];
	m_sPrintTmp = m_jStyled_writer.write(m_Object_Data_Ctrl_Msg);
	cout<<m_sPrintTmp<<endl;
	return m_sPrintTmp.data();

}

/**
 * @brief GetPresence_Msg()
 *
 * 返回接收GetPresence_Msg指针
 * @author N. W. J.
 * 
 * @param None. 
 *
 * @return GetPresence_Msg指针
  *		
 */
const char* ClientRec::GetPresence_Msg()
{
	m_Presence_Msg = m_json_Object["Presence_Msg"];
	m_sPrintTmp = m_jStyled_writer.write(m_Presence_Msg);
	cout<<m_sPrintTmp<<endl;
	return m_sPrintTmp.data();

}

/**
 * @brief GetRelay_Ctrl_Msg()
 *
 * 返回接收GetRelay_Ctrl_Msg指针
 * @author N. W. J.
 * 
 * @param None. 
 *
 * @return GetRelay_Ctrl_Msg指针
  *		
 */
const char* ClientRec::GetRelay_Ctrl_Msg()
{
	m_Relay_Ctrl_Msg = m_json_Object["Relay_Ctrl_Msg"];
	m_sPrintTmp = m_jStyled_writer.write(m_Relay_Ctrl_Msg);
	cout<<m_sPrintTmp<<endl;
	return m_sPrintTmp.data();

}

/**
 * @brief GetStatus_Msg()
 *
 * 返回接收GetStatus_Msg指针
 * @author N. W. J.
 * 
 * @param None. 
 *
 * @return GetStatus_Msg指针
  *		
 */
const char* ClientRec::GetStatus_Msg()
{
	m_Status_Msg = m_json_Object["Status_Msg"];
	m_sPrintTmp = m_jStyled_writer.write(m_Status_Msg);
	cout<<m_sPrintTmp<<endl;
	return m_sPrintTmp.data();

}

/**
 * @brief GetTime_Msg()
 *
 * 返回接收GetTime_Msg指针
 * @author N. W. J.
 * 
 * @param None. 
 *
 * @return GetTime_Msg指针
  *		
 */
const char* ClientRec::GetTime_Msg()
{
	m_Time_Msg = m_json_Object["Time_Msg"];
	m_sPrintTmp = m_jStyled_writer.write(m_Time_Msg);
	cout<<m_sPrintTmp<<endl;
	return m_sPrintTmp.data();

}

/**
 * @brief GetTriggered_Obj_Msg()
 *
 * 返回接收GetTriggered_Obj_Msg指针
 * @author N. W. J.
 * 
 * @param None. 
 *
 * @return GetTriggered_Obj_Msg指针
  *		
 */
const char* ClientRec::GetTriggered_Obj_Msg()
{
	m_Triggered_Obj_Msg = m_json_Object["Triggered_Obj_Msg"];
	m_sPrintTmp = m_jStyled_writer.write(m_Triggered_Obj_Msg);
	cout<<m_sPrintTmp<<endl;
	return m_sPrintTmp.data();

}

/**
 * @brief GetWrong_Dir_Msg()
 *
 * 返回接收GetWrong_Dir_Msg指针
 * @author N. W. J.
 * 
 * @param None. 
 *
 * @return GetWrong_Dir_Msg指针
  *		
 */
const char* ClientRec::GetWrong_Dir_Msg()
{
	m_Wrong_Dir_Msg = m_json_Object["Wrong_Dir_Msg"];
	m_sPrintTmp = m_jStyled_writer.write(m_Wrong_Dir_Msg);
	cout<<m_sPrintTmp<<endl;
	return m_sPrintTmp.data();
}

/**
 * @brief ~ClientRec()
 *
 * 
 * @author N. W. J.
 * 
 * @param None. 
 *
 * @return None.
 */
ClientRec::~ClientRec()
{
	//释放内存
	delete [] m_pRecBuffer;
	delete [] m_pRecResult;
	cout<<"All Over!"<<endl;

}

