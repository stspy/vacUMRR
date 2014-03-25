/**
 * @file server.cpp
 * @brief
 *	
 *
 * @see server
 *
 * @author N. W. J.
 * @version 0.1.0
 * @date 2014/02/26
 */

/** include files **/
#include <QtGui>
#include <QTextStream>
#include "server.h"
#include <mysql.h>

/**
 * @brief vacServerDialog()
 *
 * 
 * @author N. W. J.
 * 
 * @param None. 
 *
 * @return None.
 */
vacServerDialog::vacServerDialog(QWidget *parent) : QDialog(parent)
{
	
	pRecNetdata = new vacRecNetData;
	
	///标签和输入栏
	RecPort = new QLabel(tr("Rec Port:"));
	RecAddress = new QLabel(tr("Rec IP :"));
	RecPortLine = new QLineEdit;
	RecAddressLine = new QLineEdit;

	SendPort = new QLabel(tr("Self Port:"));
	SendAddress = new QLabel(tr("Self IP :"));
	SendPortLine = new QLineEdit;
	SendAddressLine = new QLineEdit;

	Host = new QLabel(tr("Host:"));
	User = new QLabel(tr("User:"));
	Passwd = new QLabel(tr("Passwd:"));
	DBname = new QLabel(tr("DBname:"));
	DBport = new QLabel(tr("DBport:"));
	HostLine= new QLineEdit;
	UserLine= new QLineEdit;
	PasswdLine= new QLineEdit;
	DBnameLine= new QLineEdit;
	DBportLine= new QLineEdit;

	//限制输入的端口号范围0~65535
	QValidator* val_port = new QIntValidator( 0, 65535, this );
	RecPortLine->setValidator(val_port); 
	SendPortLine->setValidator(val_port);

	ShowText = new QTextEdit;
	ShowText->setReadOnly(true);

	//IP地址的正则表达式
	QRegExp regex("(?:(?:25[0-5]|2[0-4]\\d|((1\\d{2})|([1-9]?\\d)))\\.){3}(?:25[0-5]|2[0-4]\\d|((1\\d{2})|([1-9]?\\d)))");
	QValidator *val_addr = new QRegExpValidator(regex, this );
	RecAddressLine->setValidator(val_addr);
	SendAddressLine->setValidator(val_addr);

	//获取配置按键
	ShowInfoButton = new QPushButton(tr("Get Info"));
	ShowInfoButton->setDefault(true);
	ShowInfoButton->setEnabled(true);

	//连接服务器按键
	ConnectSrvButton = new QPushButton(tr("Connect Server"));
	ConnectSrvButton->setDefault(true);
	ConnectSrvButton->setEnabled(true);

	//接收数据按键
	RecButton = new QPushButton(tr("Receive"));
	RecButton->setDefault(true);
	RecButton->setEnabled(true);

	//停止接收数据按键
	StopRecButton = new QPushButton(tr("Stop Receive"));
	StopRecButton->setDefault(true);
	StopRecButton->setEnabled(true);

	//监听客户端按键
	ListenCliButton = new QPushButton(tr("Listen Client"));
	ListenCliButton->setDefault(true);
	ListenCliButton->setEnabled(true);

	//发送数据按键
	SendButton = new QPushButton(tr("Send"));
	SendButton->setDefault(true);
	SendButton->setEnabled(true);

	//停止发送按键
	StopSendButton = new QPushButton(tr("Stop Send"));
	StopSendButton->setDefault(true);
	StopSendButton->setEnabled(true);

	//建立 按键-槽
	connect(ShowInfoButton, SIGNAL(clicked()),
		this, SLOT(GetIPInfo()));
	connect(ConnectSrvButton, SIGNAL(clicked()),
		this, SLOT(ConnectSever()));
	connect(RecButton, SIGNAL(clicked()),
		this, SLOT(RecFile()));
	connect(StopRecButton, SIGNAL(clicked()),
		this, SLOT(StopRec()));
	connect(ListenCliButton, SIGNAL(clicked()),
		this, SLOT(ListenClient()));
	connect(SendButton, SIGNAL(clicked()),
		this, SLOT(SendFile()));
	connect(StopSendButton, SIGNAL(clicked()),
		this, SLOT(StopSend()));
	
	//界面布局
	QVBoxLayout *LeftLayout = new QVBoxLayout;
	LeftLayout->addWidget(RecAddress);
	LeftLayout->addWidget(RecPort);
	LeftLayout->addWidget(SendAddress);
	LeftLayout->addWidget(SendPort);
	LeftLayout->addWidget(Host);
	LeftLayout->addWidget(User);
	LeftLayout->addWidget(Passwd);
	LeftLayout->addWidget(DBname);
	LeftLayout->addWidget(DBport);

	QVBoxLayout *MidLayout = new QVBoxLayout;
	MidLayout->addWidget(RecAddressLine);
	MidLayout->addWidget(RecPortLine);
	MidLayout->addWidget(SendAddressLine);
	MidLayout->addWidget(SendPortLine);
	MidLayout->addWidget(HostLine);
	MidLayout->addWidget(UserLine);
	MidLayout->addWidget(PasswdLine);
	MidLayout->addWidget(DBnameLine);
	MidLayout->addWidget(DBportLine);

	QVBoxLayout *RightLayout = new QVBoxLayout;
	RightLayout->addWidget(ShowInfoButton);
	RightLayout->addWidget(ConnectSrvButton);
	RightLayout->addWidget(ListenCliButton);
	RightLayout->addWidget(RecButton);
	RightLayout->addWidget(SendButton);
	RightLayout->addWidget(StopRecButton);
	RightLayout->addWidget(StopSendButton);
	
	QHBoxLayout *UpLayout = new QHBoxLayout;
	UpLayout->addLayout(LeftLayout);
	UpLayout->addLayout(MidLayout);
	UpLayout->addLayout(RightLayout);


	QVBoxLayout *MainLayout = new QVBoxLayout;
	MainLayout->addLayout(UpLayout);
	MainLayout->addWidget(ShowText);

	setLayout(MainLayout);
	setWindowTitle(tr("SERVER"));
	setFixedHeight(sizeHint().height());
	nflag_db = 0;
	nSend_Time = 0;
	PrintTmp = "";

}

/**
 * @brief GetIPInfo()
 *
 * 获取服务器IP和端口
 * @author N. W. J.
 * 
 * @param None. 
 *
 * @return None.
 */
void vacServerDialog:: GetIPInfo()
{
#if TEST_MODE
	sRecAdd  = "192.168.6.124";
	nRecPort = "9988";
	sSelfAdd = "192.168.6.118";
	nSelfPort = "7777";
	sHost = "localhost";
	sUser = "test";
	sPasswd = "12345";
	sDBname = "dbsqltest";
	nDBport = "3306";

#else
 	sRecAdd  = RecAddressLine->text();
 	nRecPort = RecPortLine->text();
 	sSelfAdd =SendAddressLine->text();
 	nSelfPort = SendPortLine->text();

	sHost = HostLine->text();
	sUser = UserLine->text();
	sPasswd = PasswdLine->text();
	sDBname = DBnameLine->text();
	nDBport = DBportLine->text();

#endif

	//显示获取的IP和端口
	ShowText->insertPlainText("Get Info Successfully !");
	ShowText->insertPlainText("\nIP :");
	ShowText->insertPlainText(sRecAdd);
	ShowText->insertPlainText("\nPort :");
	ShowText->insertPlainText(nRecPort);
	ShowText->insertPlainText("\nIP :");
	ShowText->insertPlainText(sSelfAdd);
	ShowText->insertPlainText("\nPort :");
	ShowText->insertPlainText(nSelfPort);
	ShowText->insertPlainText("\nHost :");
	ShowText->insertPlainText(sHost);
	ShowText->insertPlainText("\nUser :");
	ShowText->insertPlainText(sUser);
	ShowText->insertPlainText("\nPasswd :");
	ShowText->insertPlainText(sPasswd);
	ShowText->insertPlainText("\nDBname :");
	ShowText->insertPlainText(sDBname);
	ShowText->insertPlainText("\nDBport :");
	ShowText->insertPlainText(nDBport);	
	
	//传递IP和端口
	pRecNetdata->GetRecAddr(sRecAdd.toStdString());
	pRecNetdata->GetRecPort(nRecPort.toUInt());
	pRecNetdata->GetSelfAddr(sSelfAdd.toStdString());
	pRecNetdata->GetSelfPort(nSelfPort.toUInt());

	//传递数据库变量
	pRecNetdata->GetHost(sHost.toStdString());
	pRecNetdata->GetUser(sUser.toStdString());
	pRecNetdata->GetPasswd(sPasswd.toStdString());
	pRecNetdata->GetDBname(sDBname.toStdString());
	pRecNetdata->GetDBport(nDBport.toUInt());
}

/**
 * @brief ConnectSever()
 *
 * 连接服务器
 * @author N. W. J.
 * 
 * @param None. 
 *
 * @return None.
 */
void vacServerDialog::ConnectSever()
{
	//初始化套接字，IP，端口
	pRecNetdata->InitTcp_rec();
	PrintInfo(pRecNetdata->BackInfo());
	
	//连接服务器
	pRecNetdata->ConnectServer();
	PrintInfo("\n");
	PrintInfo(pRecNetdata->BackInfo());
}

/**
 * @brief RecFile()
 *
 * 接收数据
 * @author N. W. J.
 * 
 * @param None. 
 *
 * @return None.
 */
void vacServerDialog::RecFile()
{
	QString strValue;
	ShowText->clear();
	pRecNetdata->RecData();

	
	PrintInfo(pRecNetdata->BackInfo());
	nSend_Time = pRecNetdata->Translate();
	strValue = tr("%1").arg(nSend_Time);
	ShowText->insertPlainText("\nTranslate :");
	ShowText->insertPlainText(strValue);
	ShowText->insertPlainText(" data packet !");

	
}

/**
 * @brief StopRec()
 *
 * 停止接收数据
 * @author N. W. J.
 * 
 * @param None. 
 *
 * @return None.
 */
void vacServerDialog::StopRec()
{
	pRecNetdata->StopRecData();
	ShowText->insertPlainText("\nStop Receive !");
}

/**
 * @brief ListenClient()
 *
 * 监听客户端
 * @author N. W. J.
 * 
 * @param None. 
 *
 * @return None.
 */
void vacServerDialog::ListenClient()
{
	//初始化套接字，IP，端口
	pRecNetdata->InitTcp_send();
	PrintInfo(pRecNetdata->BackInfo());
	
	//监听并等待客户端请求
	pRecNetdata->AcceptClient();
	PrintInfo(pRecNetdata->BackInfo());
}

/**
 * @brief SendFile()
 *
 * 发送文件
 * @author N. W. J.
 * 
 * @param None. 
 *
 * @return None.
 */
void vacServerDialog::SendFile()
{
	int nTmp;
	QString strValue;

	if (nSend_Time >= 1)
	{
		nTmp = pRecNetdata->SendData();
		PrintTmp = QString::number(nTmp,10);
		//显示操作提示

		strValue = tr("%1").arg(nSend_Time);
		ShowText->insertPlainText("\n ");
		ShowText->insertPlainText(strValue);
		ShowText->insertPlainText(":  Send   ");
		ShowText->insertPlainText(PrintTmp);
		ShowText->insertPlainText("   byte");
		
		nSend_Time--;

		if (nSend_Time == 0)
		{
			ShowText->insertPlainText("\n Please Receive the data again !");
		}
	}
	
	
	
}

/**
 * @brief StopSend()
 *
 * 停止发送
 * @author N. W. J.
 * 
 * @param None. 
 *
 * @return None.
 */
void vacServerDialog::StopSend()
{
	pRecNetdata->StopSendData();
	ShowText->insertPlainText("\nStop Send !");
}

/**
 * @brief PrintInfo()
 *
 * 
 * @author N. W. J.
 * 
 * @param str：需要显示的字符串. 
 *
 * @return None.
 */
void vacServerDialog::PrintInfo(std::string str)
{
	PrintTmp = QString(QString::fromLocal8Bit(str.c_str()));
	ShowText->insertPlainText(PrintTmp);
}