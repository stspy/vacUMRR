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
	
	///��ǩ��������
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

	//��������Ķ˿ںŷ�Χ0~65535
	QValidator* val_port = new QIntValidator( 0, 65535, this );
	RecPortLine->setValidator(val_port); 
	SendPortLine->setValidator(val_port);

	ShowText = new QTextEdit;
	ShowText->setReadOnly(true);

	//IP��ַ��������ʽ
	QRegExp regex("(?:(?:25[0-5]|2[0-4]\\d|((1\\d{2})|([1-9]?\\d)))\\.){3}(?:25[0-5]|2[0-4]\\d|((1\\d{2})|([1-9]?\\d)))");
	QValidator *val_addr = new QRegExpValidator(regex, this );
	RecAddressLine->setValidator(val_addr);
	SendAddressLine->setValidator(val_addr);

	//��ȡ���ð���
	ShowInfoButton = new QPushButton(tr("Get Info"));
	ShowInfoButton->setDefault(true);
	ShowInfoButton->setEnabled(true);

	//���ӷ���������
	ConnectSrvButton = new QPushButton(tr("Connect Server"));
	ConnectSrvButton->setDefault(true);
	ConnectSrvButton->setEnabled(true);

	//�������ݰ���
	RecButton = new QPushButton(tr("Receive"));
	RecButton->setDefault(true);
	RecButton->setEnabled(true);

	//ֹͣ�������ݰ���
	StopRecButton = new QPushButton(tr("Stop Receive"));
	StopRecButton->setDefault(true);
	StopRecButton->setEnabled(true);

	//�����ͻ��˰���
	ListenCliButton = new QPushButton(tr("Listen Client"));
	ListenCliButton->setDefault(true);
	ListenCliButton->setEnabled(true);

	//�������ݰ���
	SendButton = new QPushButton(tr("Send"));
	SendButton->setDefault(true);
	SendButton->setEnabled(true);

	//ֹͣ���Ͱ���
	StopSendButton = new QPushButton(tr("Stop Send"));
	StopSendButton->setDefault(true);
	StopSendButton->setEnabled(true);

	//���� ����-��
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
	
	//���沼��
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
 * ��ȡ������IP�Ͷ˿�
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

	//��ʾ��ȡ��IP�Ͷ˿�
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
	
	//����IP�Ͷ˿�
	pRecNetdata->GetRecAddr(sRecAdd.toStdString());
	pRecNetdata->GetRecPort(nRecPort.toUInt());
	pRecNetdata->GetSelfAddr(sSelfAdd.toStdString());
	pRecNetdata->GetSelfPort(nSelfPort.toUInt());

	//�������ݿ����
	pRecNetdata->GetHost(sHost.toStdString());
	pRecNetdata->GetUser(sUser.toStdString());
	pRecNetdata->GetPasswd(sPasswd.toStdString());
	pRecNetdata->GetDBname(sDBname.toStdString());
	pRecNetdata->GetDBport(nDBport.toUInt());
}

/**
 * @brief ConnectSever()
 *
 * ���ӷ�����
 * @author N. W. J.
 * 
 * @param None. 
 *
 * @return None.
 */
void vacServerDialog::ConnectSever()
{
	//��ʼ���׽��֣�IP���˿�
	pRecNetdata->InitTcp_rec();
	PrintInfo(pRecNetdata->BackInfo());
	
	//���ӷ�����
	pRecNetdata->ConnectServer();
	PrintInfo("\n");
	PrintInfo(pRecNetdata->BackInfo());
}

/**
 * @brief RecFile()
 *
 * ��������
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
 * ֹͣ��������
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
 * �����ͻ���
 * @author N. W. J.
 * 
 * @param None. 
 *
 * @return None.
 */
void vacServerDialog::ListenClient()
{
	//��ʼ���׽��֣�IP���˿�
	pRecNetdata->InitTcp_send();
	PrintInfo(pRecNetdata->BackInfo());
	
	//�������ȴ��ͻ�������
	pRecNetdata->AcceptClient();
	PrintInfo(pRecNetdata->BackInfo());
}

/**
 * @brief SendFile()
 *
 * �����ļ�
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
		//��ʾ������ʾ

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
 * ֹͣ����
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
 * @param str����Ҫ��ʾ���ַ���. 
 *
 * @return None.
 */
void vacServerDialog::PrintInfo(std::string str)
{
	PrintTmp = QString(QString::fromLocal8Bit(str.c_str()));
	ShowText->insertPlainText(PrintTmp);
}