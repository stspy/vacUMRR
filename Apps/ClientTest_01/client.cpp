/**
 * @file client.cpp
 * @brief
 *	
 *
 * @see client
 *
 * @author N. W. J.
 * @version 0.1.0
 * @date 2014/02/26
 */

/** include files **/
#include <QtGui>
#include <QTextStream>
#include "client.h"

/**
 * @brief ClientDialog()
 *
 * 
 * @author N. W. J.
 * 
 * @param None. 
 *
 * @return None.
 */
ClientDialog::ClientDialog(QWidget *parent)
	: QDialog(parent)
{
	
	PrintTmp = "";

	pRecData = new ClientRec;
	
	///网络端口Port 和 IP地址
	RecPort = new QLabel(tr("Rec Port:"));
	RecAddress = new QLabel(tr("Rec IP :"));
	RecPortLine = new QLineEdit;
	RecAddressLine = new QLineEdit;

	//限制输入的端口号范围0~65535
	QValidator* val_port = new QIntValidator( 0, 65535, this );
	RecPortLine->setValidator(val_port); 

	//IP地址的正则表达式
	QRegExp regex("(?:(?:25[0-5]|2[0-4]\\d|((1\\d{2})|([1-9]?\\d)))\\.){3}(?:25[0-5]|2[0-4]\\d|((1\\d{2})|([1-9]?\\d)))");
	QValidator *val_addr = new QRegExpValidator(regex, this );
	RecAddressLine->setValidator(val_addr);

	//获取配置按键
	GetInfoButton = new QPushButton(tr("Get Info"));
	GetInfoButton->setDefault(true);
	GetInfoButton->setEnabled(true);

	//连接服务器按键
	ConnectButton = new QPushButton(tr("Connect Server"));
	ConnectButton->setDefault(true);
	ConnectButton->setEnabled(true);

	//接收数据按键
	RecButton = new QPushButton(tr("Receive"));
	RecButton->setDefault(true);
	RecButton->setEnabled(true);

	//停止接收按键
	StopButton = new QPushButton(tr("Stop"));
	StopButton->setDefault(true);
	StopButton->setEnabled(true);

	//获取Feature Msg 1按键
	Feature_Msg_1Button = new QPushButton(tr("Feature Msg 1"));
	Feature_Msg_1Button->setDefault(true);
	Feature_Msg_1Button->setEnabled(true);

	//获取Feature Msg 2按键
	Feature_Msg_2Button = new QPushButton(tr("Feature Msg 2"));
	Feature_Msg_2Button->setDefault(true);
	Feature_Msg_2Button->setEnabled(true);

	//获取Info Msg 1按键
	Info_Msg_1Button = new QPushButton(tr("Info Msg 1"));
	Info_Msg_1Button->setDefault(true);
	Info_Msg_1Button->setEnabled(true);

	//获取Info Msg 2按键
	Info_Msg_2Button = new QPushButton(tr("Info Msg 2"));
	Info_Msg_2Button->setDefault(true);
	Info_Msg_2Button->setEnabled(true);

	//获取Object Data 1 Ms按键
	Object_Data_1_MsgButton = new QPushButton(tr("Object Data 1 Msg"));
	Object_Data_1_MsgButton->setDefault(true);
	Object_Data_1_MsgButton->setEnabled(true);

	//获取Object Data Ctrl_Msg按键
	Object_Data_Ctrl_MsgButton = new QPushButton(tr("Object Data Ctrl_Msg"));
	Object_Data_Ctrl_MsgButton->setDefault(true);
	Object_Data_Ctrl_MsgButton->setEnabled(true);

	//获取Presence Msg按键
	Presence_MsgButton = new QPushButton(tr("Presence Msg"));
	Presence_MsgButton->setDefault(true);
	Presence_MsgButton->setEnabled(true);

	//获取Relay Ctrl Msg按键
	Relay_Ctrl_MsgButton = new QPushButton(tr("Relay Ctrl Msg"));
	Relay_Ctrl_MsgButton->setDefault(true);
	Relay_Ctrl_MsgButton->setEnabled(true);

	//获取Status Msg按键
	Status_MsgButton = new QPushButton(tr("Status Msg"));
	Status_MsgButton->setDefault(true);
	Status_MsgButton->setEnabled(true);

	//获取Time Msg按键
	Time_MsgButton = new QPushButton(tr("Time Msg"));
	Time_MsgButton->setDefault(true);
	Time_MsgButton->setEnabled(true);

	//获取Triggered Obj Msg按键
	Triggered_Obj_MsgButton = new QPushButton(tr("Triggered Obj Msg"));
	Triggered_Obj_MsgButton->setDefault(true);
	Triggered_Obj_MsgButton->setEnabled(true);

	//获取Wrong Dir Msg按键
	Wrong_Dir_MsgButton = new QPushButton(tr("Wrong Dir Msg"));
	Wrong_Dir_MsgButton->setDefault(true);
	Wrong_Dir_MsgButton->setEnabled(true);

	//获取All Info按键
	AllButton = new QPushButton(tr("All Info"));
	AllButton->setDefault(true);
	AllButton->setEnabled(true);

	//显示提示信息
	ShowText_Info = new QTextEdit;
	ShowText_Info->setReadOnly(true);

	//显示数据
	ShowText_Content = new QTextEdit;
	ShowText_Content->setReadOnly(true);

	//建立 按键-槽
	connect(GetInfoButton, SIGNAL(clicked()),
		this, SLOT(GetIPInfo()));
	connect(ConnectButton, SIGNAL(clicked()),
		this, SLOT(Connect()));
	connect(RecButton, SIGNAL(clicked()),
		this, SLOT(RecFile()));
	connect(StopButton, SIGNAL(clicked()),
		this, SLOT(StopRec()));
	connect(Feature_Msg_1Button, SIGNAL(clicked()),
		this, SLOT(GetFeature_Msg_1()));
	connect(Feature_Msg_2Button, SIGNAL(clicked()),
		this, SLOT(GetFeature_Msg_2()));
	connect(Info_Msg_1Button, SIGNAL(clicked()),
		this, SLOT(GetInfo_Msg_1()));
	connect(Info_Msg_2Button, SIGNAL(clicked()),
		this, SLOT(GetInfo_Msg_2()));
	connect(Object_Data_1_MsgButton, SIGNAL(clicked()),
		this, SLOT(GetObject_Data_1_Msg()));
	connect(Object_Data_Ctrl_MsgButton, SIGNAL(clicked()),
		this, SLOT(GetObject_Data_Ctrl_Msg()));
	connect(Presence_MsgButton, SIGNAL(clicked()),
		this, SLOT(GetPresence_Msg()));
	connect(Relay_Ctrl_MsgButton, SIGNAL(clicked()),
		this, SLOT(GetRelay_Ctrl_Msg()));
	connect(Status_MsgButton, SIGNAL(clicked()),
		this, SLOT(GetStatus_Msg()));
	connect(Time_MsgButton, SIGNAL(clicked()),
		this, SLOT(GetTime_Msg()));
	connect(Triggered_Obj_MsgButton, SIGNAL(clicked()),
		this, SLOT(GetTriggered_Obj_Msg()));
	connect(Wrong_Dir_MsgButton, SIGNAL(clicked()),
		this, SLOT(GetWrong_Dir_Msg()));
	connect(AllButton, SIGNAL(clicked()),
		this, SLOT(GetAll()));

	//界面布局
	QVBoxLayout *LeftLayout = new QVBoxLayout;
	LeftLayout->addWidget(RecAddress);
	LeftLayout->addWidget(RecPort);

	QVBoxLayout *MidLayout = new QVBoxLayout;
	MidLayout->addWidget(RecAddressLine);
	MidLayout->addWidget(RecPortLine);

	QVBoxLayout *RightLayout = new QVBoxLayout;
	RightLayout->addWidget(GetInfoButton);
	RightLayout->addWidget(ConnectButton);
	RightLayout->addWidget(RecButton);
	RightLayout->addWidget(StopButton);

	QHBoxLayout *UpLayout = new QHBoxLayout;
	UpLayout->addLayout(LeftLayout);
	UpLayout->addLayout(MidLayout);
	UpLayout->addLayout(RightLayout);

	QVBoxLayout *MainLeftLayout =new QVBoxLayout; 
	MainLeftLayout->addLayout(UpLayout);
	MainLeftLayout->addWidget(ShowText_Info);

	QVBoxLayout *Right_Button = new QVBoxLayout;
	Right_Button->addWidget(AllButton);
	Right_Button->addWidget(Feature_Msg_1Button);
	Right_Button->addWidget(Feature_Msg_2Button);
	Right_Button->addWidget(Info_Msg_1Button);
	Right_Button->addWidget(Info_Msg_2Button);
	Right_Button->addWidget(Object_Data_1_MsgButton);
	Right_Button->addWidget(Object_Data_Ctrl_MsgButton);
	Right_Button->addWidget(Presence_MsgButton);
	Right_Button->addWidget(Relay_Ctrl_MsgButton);	
	Right_Button->addWidget(Status_MsgButton);
	Right_Button->addWidget(Time_MsgButton);
	Right_Button->addWidget(Triggered_Obj_MsgButton);
	Right_Button->addWidget(Wrong_Dir_MsgButton);

	QHBoxLayout *MainLayout = new QHBoxLayout;
	MainLayout->addLayout(MainLeftLayout);
	MainLayout->addWidget(ShowText_Content);
	MainLayout->addLayout(Right_Button);

	setLayout(MainLayout);
	setWindowTitle(tr("CLIENT"));
	setFixedHeight(sizeHint().height());

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
void ClientDialog:: GetIPInfo()
{
#if TEST_MODE
	sRecAdd  = "192.168.6.118";
	nRecPort = "7777";
#else
 	sRecAdd  = RecAddressLine->text();
 	nRecPort = RecPortLine->text();
#endif
	
	//显示获取的IP和端口
	ShowText_Info->insertPlainText("Get Info Successfully !");
	ShowText_Info->insertPlainText("\nIP :");
	ShowText_Info->insertPlainText(sRecAdd);
	ShowText_Info->insertPlainText("\nPort :");
	ShowText_Info->insertPlainText(nRecPort);

	//传递IP和端口
	pRecData->GetRecAddr(sRecAdd.toStdString());
	pRecData->GetRecPort(nRecPort.toUInt());
}

/**
 * @brief Connect()
 *
 * 连接服务器
 * @author N. W. J.
 * 
 * @param None. 
 *
 * @return None.
 */
void ClientDialog::Connect()
{
	//初始化套接字，IP，端口
	pRecData->InitTcp();
	PrintInfo(pRecData->BackInfo());

	//连接服务器
	pRecData->ConnectServer();
	PrintInfo(pRecData->BackInfo());
}

/**
 * @brief RecFile()
 *
 * 接收文件
 * @author N. W. J.
 * 
 * @param None. 
 *
 * @return None.
 */
void ClientDialog::RecFile()
{
	int nTmp;
	
	//开始接收数据
	nTmp = pRecData->RecData();

	//显示操作提示
	PrintTmp = QString::number(nTmp,10);
	ShowText_Info->insertPlainText("\nReceive   ");
	ShowText_Info->insertPlainText(PrintTmp);
	ShowText_Info->insertPlainText("   byte");
	pRecData->PreTransDatatoJson();

}

/**
 * @brief GetAll()
 *
 * 获取Json类所有信息
 * @author N. W. J.
 * 
 * @param None. 
 *
 * @return None.
 */
void ClientDialog:: GetAll()
{
	ShowText_Content->clear();
	PrintTmp = QString(QLatin1String(pRecData->GetAll()));
	ShowText_Content->insertPlainText(PrintTmp);
}

/**
 * @brief GetFeature_Msg_1()
 *
 * 获取GetFeature_Msg_1信息
 * @author N. W. J.
 * 
 * @param None. 
 *
 * @return None.
 */
void ClientDialog:: GetFeature_Msg_1()
{
	ShowText_Content->clear();
	PrintTmp = QString(QLatin1String(pRecData->GetFeature_Msg_1()));
	ShowText_Content->insertPlainText(PrintTmp);

}

/**
 * @brief GetFeature_Msg_2()
 *
 * 获取GetFeature_Msg_2信息
 * @author N. W. J.
 * 
 * @param None. 
 *
 * @return None.
 */
void ClientDialog:: GetFeature_Msg_2()
{
	ShowText_Content->clear();
	PrintTmp = QString(QLatin1String(pRecData->GetFeature_Msg_2()));
	ShowText_Content->insertPlainText(PrintTmp);
}

/**
 * @brief GetInfo_Msg_1()
 *
 * 获取GetInfo_Msg_1信息
 * @author N. W. J.
 * 
 * @param None. 
 *
 * @return None.
 */
void ClientDialog:: GetInfo_Msg_1()
{
	ShowText_Content->clear();
	PrintTmp = QString(QLatin1String(pRecData->GetInfo_Msg_1()));
	ShowText_Content->insertPlainText(PrintTmp);
}

/**
 * @brief GetInfo_Msg_2()
 *
 * 获取GetInfo_Msg_2信息
 * @author N. W. J.
 * 
 * @param None. 
 *
 * @return None.
 */
void ClientDialog:: GetInfo_Msg_2()
{
	ShowText_Content->clear();
	PrintTmp = QString(QLatin1String(pRecData->GetInfo_Msg_2()));
	ShowText_Content->insertPlainText(PrintTmp);
}

/**
 * @brief GetObject_Data_1_Ms()
 *
 * 获取GetObject_Data_1_Ms信息
 * @author N. W. J.
 * 
 * @param None. 
 *
 * @return None.
 */
void ClientDialog:: GetObject_Data_1_Msg()
{
	ShowText_Content->clear();
	PrintTmp = QString(QLatin1String(pRecData->GetObject_Data_1_Msg()));
	ShowText_Content->insertPlainText(PrintTmp);
}

/**
 * @brief GetObject_Data_Ctrl_Msg()
 *
 * 获取GetObject_Data_Ctrl_Msg信息
 * @author N. W. J.
 * 
 * @param None. 
 *
 * @return None.
 */
void ClientDialog:: GetObject_Data_Ctrl_Msg()
{
	ShowText_Content->clear();
	PrintTmp = QString(QLatin1String(pRecData->GetObject_Data_Ctrl_Msg()));
	ShowText_Content->insertPlainText(PrintTmp);
}

/**
 * @brief GetPresence_Msg()
 *
 * 获取GetPresence_Msg信息
 * @author N. W. J.
 * 
 * @param None. 
 *
 * @return None.
 */
void ClientDialog:: GetPresence_Msg()
{
	ShowText_Content->clear();
	PrintTmp = QString(QLatin1String(pRecData->GetPresence_Msg()));
	ShowText_Content->insertPlainText(PrintTmp);
}

/**
 * @brief GetRelay_Ctrl_Msg()
 *
 * 获取GetRelay_Ctrl_Msg信息
 * @author N. W. J.
 * 
 * @param None. 
 *
 * @return None.
 */
void ClientDialog:: GetRelay_Ctrl_Msg()
{
	ShowText_Content->clear();
	PrintTmp = QString(QLatin1String(pRecData->GetRelay_Ctrl_Msg()));
	ShowText_Content->insertPlainText(PrintTmp);
}

/**
 * @brief GetStatus_Msg()
 *
 * 获取GetStatus_Msg信息
 * @author N. W. J.
 * 
 * @param None. 
 *
 * @return None.
 */
void ClientDialog:: GetStatus_Msg()
{
	ShowText_Content->clear();
	PrintTmp = QString(QLatin1String(pRecData->GetStatus_Msg()));
	ShowText_Content->insertPlainText(PrintTmp);
}

/**
 * @brief GetTime_Msg()
 *
 * 获取GetTime_Msg信息
 * @author N. W. J.
 * 
 * @param None. 
 *
 * @return None.
 */
void ClientDialog:: GetTime_Msg()
{
	ShowText_Content->clear();
	PrintTmp = QString(QLatin1String(pRecData->GetTime_Msg()));
	ShowText_Content->insertPlainText(PrintTmp);
}

/**
 * @brief GetTriggered_Obj_Msg()
 *
 * 获取GetTriggered_Obj_Msg信息
 * @author N. W. J.
 * 
 * @param None. 
 *
 * @return None.
 */
void ClientDialog:: GetTriggered_Obj_Msg()
{
	ShowText_Content->clear();
	PrintTmp = QString(QLatin1String(pRecData->GetTriggered_Obj_Msg()));
	ShowText_Content->insertPlainText(PrintTmp);
}

/**
 * @brief GetWrong_Dir_Msg()
 *
 * 获取GetWrong_Dir_Msg信息
 * @author N. W. J.
 * 
 * @param None. 
 *
 * @return None.
 */
void ClientDialog:: GetWrong_Dir_Msg()
{
	ShowText_Content->clear();
	PrintTmp = QString(QLatin1String(pRecData->GetWrong_Dir_Msg()));
	ShowText_Content->insertPlainText(PrintTmp);
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
void ClientDialog::StopRec()
{
	pRecData->StopRecData();
	ShowText_Info->insertPlainText("\nStop Receive !");
}

/**
 * @brief 打印提示信息()
 *
 * 获取信息
 * @author N. W. J.
 * 
 * @param str：要打印的字符串 
 *
 * @return None.
 */
void ClientDialog::PrintInfo(std::string str)
{
	PrintTmp = QString(QString::fromLocal8Bit(str.c_str()));
	ShowText_Info->insertPlainText(PrintTmp);
}