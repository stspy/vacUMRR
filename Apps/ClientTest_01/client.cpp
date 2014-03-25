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
	
	///����˿�Port �� IP��ַ
	RecPort = new QLabel(tr("Rec Port:"));
	RecAddress = new QLabel(tr("Rec IP :"));
	RecPortLine = new QLineEdit;
	RecAddressLine = new QLineEdit;

	//��������Ķ˿ںŷ�Χ0~65535
	QValidator* val_port = new QIntValidator( 0, 65535, this );
	RecPortLine->setValidator(val_port); 

	//IP��ַ��������ʽ
	QRegExp regex("(?:(?:25[0-5]|2[0-4]\\d|((1\\d{2})|([1-9]?\\d)))\\.){3}(?:25[0-5]|2[0-4]\\d|((1\\d{2})|([1-9]?\\d)))");
	QValidator *val_addr = new QRegExpValidator(regex, this );
	RecAddressLine->setValidator(val_addr);

	//��ȡ���ð���
	GetInfoButton = new QPushButton(tr("Get Info"));
	GetInfoButton->setDefault(true);
	GetInfoButton->setEnabled(true);

	//���ӷ���������
	ConnectButton = new QPushButton(tr("Connect Server"));
	ConnectButton->setDefault(true);
	ConnectButton->setEnabled(true);

	//�������ݰ���
	RecButton = new QPushButton(tr("Receive"));
	RecButton->setDefault(true);
	RecButton->setEnabled(true);

	//ֹͣ���հ���
	StopButton = new QPushButton(tr("Stop"));
	StopButton->setDefault(true);
	StopButton->setEnabled(true);

	//��ȡFeature Msg 1����
	Feature_Msg_1Button = new QPushButton(tr("Feature Msg 1"));
	Feature_Msg_1Button->setDefault(true);
	Feature_Msg_1Button->setEnabled(true);

	//��ȡFeature Msg 2����
	Feature_Msg_2Button = new QPushButton(tr("Feature Msg 2"));
	Feature_Msg_2Button->setDefault(true);
	Feature_Msg_2Button->setEnabled(true);

	//��ȡInfo Msg 1����
	Info_Msg_1Button = new QPushButton(tr("Info Msg 1"));
	Info_Msg_1Button->setDefault(true);
	Info_Msg_1Button->setEnabled(true);

	//��ȡInfo Msg 2����
	Info_Msg_2Button = new QPushButton(tr("Info Msg 2"));
	Info_Msg_2Button->setDefault(true);
	Info_Msg_2Button->setEnabled(true);

	//��ȡObject Data 1 Ms����
	Object_Data_1_MsgButton = new QPushButton(tr("Object Data 1 Msg"));
	Object_Data_1_MsgButton->setDefault(true);
	Object_Data_1_MsgButton->setEnabled(true);

	//��ȡObject Data Ctrl_Msg����
	Object_Data_Ctrl_MsgButton = new QPushButton(tr("Object Data Ctrl_Msg"));
	Object_Data_Ctrl_MsgButton->setDefault(true);
	Object_Data_Ctrl_MsgButton->setEnabled(true);

	//��ȡPresence Msg����
	Presence_MsgButton = new QPushButton(tr("Presence Msg"));
	Presence_MsgButton->setDefault(true);
	Presence_MsgButton->setEnabled(true);

	//��ȡRelay Ctrl Msg����
	Relay_Ctrl_MsgButton = new QPushButton(tr("Relay Ctrl Msg"));
	Relay_Ctrl_MsgButton->setDefault(true);
	Relay_Ctrl_MsgButton->setEnabled(true);

	//��ȡStatus Msg����
	Status_MsgButton = new QPushButton(tr("Status Msg"));
	Status_MsgButton->setDefault(true);
	Status_MsgButton->setEnabled(true);

	//��ȡTime Msg����
	Time_MsgButton = new QPushButton(tr("Time Msg"));
	Time_MsgButton->setDefault(true);
	Time_MsgButton->setEnabled(true);

	//��ȡTriggered Obj Msg����
	Triggered_Obj_MsgButton = new QPushButton(tr("Triggered Obj Msg"));
	Triggered_Obj_MsgButton->setDefault(true);
	Triggered_Obj_MsgButton->setEnabled(true);

	//��ȡWrong Dir Msg����
	Wrong_Dir_MsgButton = new QPushButton(tr("Wrong Dir Msg"));
	Wrong_Dir_MsgButton->setDefault(true);
	Wrong_Dir_MsgButton->setEnabled(true);

	//��ȡAll Info����
	AllButton = new QPushButton(tr("All Info"));
	AllButton->setDefault(true);
	AllButton->setEnabled(true);

	//��ʾ��ʾ��Ϣ
	ShowText_Info = new QTextEdit;
	ShowText_Info->setReadOnly(true);

	//��ʾ����
	ShowText_Content = new QTextEdit;
	ShowText_Content->setReadOnly(true);

	//���� ����-��
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

	//���沼��
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
 * ��ȡ������IP�Ͷ˿�
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
	
	//��ʾ��ȡ��IP�Ͷ˿�
	ShowText_Info->insertPlainText("Get Info Successfully !");
	ShowText_Info->insertPlainText("\nIP :");
	ShowText_Info->insertPlainText(sRecAdd);
	ShowText_Info->insertPlainText("\nPort :");
	ShowText_Info->insertPlainText(nRecPort);

	//����IP�Ͷ˿�
	pRecData->GetRecAddr(sRecAdd.toStdString());
	pRecData->GetRecPort(nRecPort.toUInt());
}

/**
 * @brief Connect()
 *
 * ���ӷ�����
 * @author N. W. J.
 * 
 * @param None. 
 *
 * @return None.
 */
void ClientDialog::Connect()
{
	//��ʼ���׽��֣�IP���˿�
	pRecData->InitTcp();
	PrintInfo(pRecData->BackInfo());

	//���ӷ�����
	pRecData->ConnectServer();
	PrintInfo(pRecData->BackInfo());
}

/**
 * @brief RecFile()
 *
 * �����ļ�
 * @author N. W. J.
 * 
 * @param None. 
 *
 * @return None.
 */
void ClientDialog::RecFile()
{
	int nTmp;
	
	//��ʼ��������
	nTmp = pRecData->RecData();

	//��ʾ������ʾ
	PrintTmp = QString::number(nTmp,10);
	ShowText_Info->insertPlainText("\nReceive   ");
	ShowText_Info->insertPlainText(PrintTmp);
	ShowText_Info->insertPlainText("   byte");
	pRecData->PreTransDatatoJson();

}

/**
 * @brief GetAll()
 *
 * ��ȡJson��������Ϣ
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
 * ��ȡGetFeature_Msg_1��Ϣ
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
 * ��ȡGetFeature_Msg_2��Ϣ
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
 * ��ȡGetInfo_Msg_1��Ϣ
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
 * ��ȡGetInfo_Msg_2��Ϣ
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
 * ��ȡGetObject_Data_1_Ms��Ϣ
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
 * ��ȡGetObject_Data_Ctrl_Msg��Ϣ
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
 * ��ȡGetPresence_Msg��Ϣ
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
 * ��ȡGetRelay_Ctrl_Msg��Ϣ
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
 * ��ȡGetStatus_Msg��Ϣ
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
 * ��ȡGetTime_Msg��Ϣ
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
 * ��ȡGetTriggered_Obj_Msg��Ϣ
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
 * ��ȡGetWrong_Dir_Msg��Ϣ
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
 * ֹͣ��������
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
 * @brief ��ӡ��ʾ��Ϣ()
 *
 * ��ȡ��Ϣ
 * @author N. W. J.
 * 
 * @param str��Ҫ��ӡ���ַ��� 
 *
 * @return None.
 */
void ClientDialog::PrintInfo(std::string str)
{
	PrintTmp = QString(QString::fromLocal8Bit(str.c_str()));
	ShowText_Info->insertPlainText(PrintTmp);
}