/**
 * @file vacNetSend.cpp
 * @brief
 *	
 *
 * @see vacNetSend
 *
 * @author N. W. J.
 * @version 0.1.0
 * @date 2014/02/26
 */


/** include files **/
#include "vacNetSend.h"

/**
 * @brief vacRecNetData()
 *
 * 
 * @author N. W. J.
 * 
 * @param None. 
 *
 * @return None.
 */
vacRecNetData::vacRecNetData()
{
	//为缓冲区申请内存并初始化相关变量
	m_pRecBuffer = new char [BUFFER_DATA_SIZE];
	m_pRecResult = new char [BUFFER_DATA_SIZE];
	m_pSendBuffer = new char [SEND_BUFFER_LEN];
	m_sRecAddr = "";
	m_nRecPort = 0;
	m_nRec_byte = 0;
	m_sSelfAddr = "";
	m_nSelfPort = 0;
	m_nSend_byte = 0;

	m_sHost = "";
	m_sUser = "";
	m_sPasswd = "";
	m_sDBname = "";
	m_nDBport = 0;
	flag_init = 0;

	//设置接收缓存大小
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
int vacRecNetData::InitTcp_rec()
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
	m_SockRec = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
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
int vacRecNetData::ConnectServer()
{
	//尝试多次与服务器建立连接
	int i;
	for (i=0; i<TRY_MAX_TIME; i++)
	{
		if(connect(m_SockRec,(SOCKADDR*)&m_SeverAddr,sizeof(SOCKADDR))== -1)
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
		m_sPrintTmp = "Connect Server OK ! Wait Server Send data ……";
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
int vacRecNetData::RecData()
{
	//接收数据，阻塞当前程序，直到接收到数据
	m_nRec_byte = recv(m_SockRec, (char *)m_pRecBuffer,
					ONCE_RECEIVE_DATA,0);
	char buffer[50];
	//接收数据有效
	if (m_nRec_byte > 0 && m_nRec_byte < BUFFER_DATA_SIZE)
	{
		cout<<"Receive "<<m_nRec_byte<<" byte"<<endl;
		
		std::sprintf(buffer,"\nReceive %d byte ", m_nRec_byte);
		m_sPrintTmp = buffer;

		///返回实际接收到的字节数
		return m_nRec_byte;
	}

	//接收数据无效
	else
	{
		cout<<"Receive Error !"<<endl;
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
void vacRecNetData::StopRecData()
{
	//关闭套接字
	closesocket(m_SockRec);
	WSACleanup();
	m_sPrintTmp = "Stop Connect Server !";
	cout<<m_sPrintTmp<<endl;
}

/**
 * @brief GetNetData()
 *
 * 对接收到的数据转存到容器中
 * @author N. W. J.
 * 
 * @param vec：接收数据容器
 *
 * @return None.
 */
void vacRecNetData::ChangeNetData()
{
	m_vec.clear();
	copy(m_pRecBuffer, m_pRecBuffer+m_nRec_byte, m_pRecResult);

	for (unsigned int i = 0;i<m_nRec_byte;i++)
	{
		INT8U temp=*(m_pRecBuffer+i);
		m_vec.push_back(temp);
	}
}

/**
 * @brief ~vacRecNetData()
 *
 * 
 * @author N. W. J.
 * 
 * @param None. 
 *
 * @return None.
 */
vacRecNetData:: ~vacRecNetData()
{ 
	//释放内存
	delete []m_pRecBuffer;
	delete []m_pRecResult;
	delete [] m_pSendBuffer;
	cout<<"RecNetData All Over!"<<endl;
}


/**
 * @brief InitTcp_send()
 *
 * 初始化网络套接字
 * @author N. W. J.
 * 
 * @param None. 
 *
 * @return 0：初始化完成 
.*	         其他：初始化错误
 */
int vacRecNetData::InitTcp_send()
{	
	int err;

	//加载套接字库
	m_wVersionRequested = MAKEWORD(1, 1);
	err = WSAStartup( m_wVersionRequested, &m_wsaData );
	if (err != 0)
	{  
		m_sPrintTmp = "WSAStartup() failed !";
		cout<<m_sPrintTmp<<endl;
		return err;  
	} 
	if ( LOBYTE(m_wsaData.wVersion) != 1 ||HIBYTE(m_wsaData.wVersion) != 1 )
	{
		WSACleanup();
		m_sPrintTmp = "Invalid WinSock version !";
		cout<<m_sPrintTmp<<endl;
		return err;
	}

	//设置通信方式为TCP
	m_SockSend = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(m_SockSend == INVALID_SOCKET)
	{
		m_sPrintTmp = "Send socket() failed !";
		cout<<m_sPrintTmp<<endl;
		return -1 ;
	}

	//发送数据时，自身的网络地址
	m_SelfAddr.sin_addr.S_un.S_addr = inet_addr(m_sSelfAddr.data());
	m_SelfAddr.sin_family = AF_INET;
	m_SelfAddr.sin_port = htons(m_nSelfPort);

	//服务器套接字与地址绑定
	if(bind(m_SockSend,(SOCKADDR * )&m_SelfAddr, sizeof(SOCKADDR))==SOCKET_ERROR)
	{
		m_sPrintTmp = "Failed bind !";
		cout<<m_sPrintTmp<<endl;
		return -1 ;
	}

	//设置发送缓存
	setsockopt(m_SockSend, SOL_SOCKET,SO_SNDBUF,(const char*)&m_nBuffer, sizeof(int));
	
	m_sPrintTmp = "\nTcp Send Init() OK !";
	cout<<m_sPrintTmp<<endl;
	return 0;

}

/**
 * @brief AcceptClient()
 *
 * 监听并接受客户端的请求
 * @author N. W. J.
 * 
 * @param None. 
 *
 * @return None.
 */
int vacRecNetData::AcceptClient()
{
	int len = sizeof SOCKADDR;

	//该端口进入监听状态
	if(listen(m_SockSend,2)==SOCKET_ERROR)
	{
		m_sPrintTmp = "Failed listen !";
		cout<<m_sPrintTmp<<endl;
		return -1 ;
	}
	cout<<"Wait Client ......\n"<<endl;

	//阻塞程序，直到客户端响应
	m_SockClient = accept(m_SockSend, (SOCKADDR*)&m_ClientAddr, &len);
	if (m_SockClient == INVALID_SOCKET)
	{
		m_sPrintTmp = "Failed accept !";
		cout<<m_sPrintTmp<<endl;
		return -1 ;
	}

	m_sPrintTmp = "Accept Client OK !";
	cout<<m_sPrintTmp<<endl;
	return 0;
}

/**
 * @brief SendData()
 *
 * 发送数据给客户端
 * @author N. W. J.
 * 
 * @param None. 
 *
 * @return m_nSend_byte：实际发送数据的大小，单位：字节
 */

int vacRecNetData::SendData()
{ 
	DataParser.ReadJsonPackage(JsonTmp);
	
	//快速写
	//m_sSend_Data = fast_writer.write(JsonTmp);
	//格式写
	m_sSend_Data = styled_writer.write(JsonTmp);

	m_pSendBuffer = (char *)m_sSend_Data.data();
	m_nStr_leng = m_sSend_Data.size();

	//直接发送，解析后的数据
	m_nSend_byte = send( m_SockClient, m_pSendBuffer, m_nStr_leng , 0); 

	cout<<"Send   "<<m_nSend_byte<<"   byte"<<endl;
	Sleep(500);

	return m_nSend_byte;

} 

/**
 * @brief StopSend()
 *
 * 断开与客户端的连接，停止发送数据
 * @author N. W. J.
 * 
 * @param None. 
 *
 * @return None.
 */
void vacRecNetData::StopSendData()
{
	//关闭套接字
	closesocket(m_SockClient);
	closesocket(m_SockSend);
	WSACleanup();
	m_sPrintTmp = "Stop Connect Client !";
	cout<<m_sPrintTmp<<endl;

}

/**
 * @brief Translate()
 *
 * 断开与客户端的连接，停止发送数据
 * @author N. W. J.
 * 
 * @param None. 
 *
 * @return None.
 */
int vacRecNetData::Translate()
{
	//把数据存到容器里面，便于解析
	ChangeNetData();
	
	if (flag_init == 0)
	{
		DataParser.SetDataBasePara(m_sUser, m_sPasswd, m_sDBname, m_sHost, m_nDBport);
		flag_init = 1;
	}
	
	int num=DataParser.ParseDataPackage(m_vec);



	return num;

}


