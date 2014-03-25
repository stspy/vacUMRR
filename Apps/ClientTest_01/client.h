/**
 * @file client.h
 * @brief
 * �ͻ��˽���
 *
 * @see client
 *
 * @author N. W. J.
 * @version 0.1.0
 * @date 2014/02/26
 */
#ifndef CLIENT_H
#define CLIENT_H

#include <QDialog>
#include <QtGui>
#include "vacNetRec.h"
#include "vacRadarCommon.h"

class QCheckBox;
class QLabel;
class QLineEdit;
class QPushButton;

/** 
 * @class ClientDialog
 * @brief �ͻ��˽��� 
 * 
 *
 * @ingroup ClientDialog
 */
class ClientDialog : public QDialog
{
	Q_OBJECT
public:
	///
	ClientDialog(QWidget *parent = 0);
	
	///���ý���IP
	std::string GetRecAddr();

	///���ý��ն˿�
	unsigned int GetRecPort();

	///��ʾ��Ϣ
	void PrintInfo(std::string str);

signals:

private slots:
	///�����ۣ���Ӧ���԰�������
	void GetIPInfo();

	///
	void Connect();

	///
	void RecFile();

	///
	void StopRec();

	///
	void GetFeature_Msg_1();

	///
	void GetFeature_Msg_2();

	///
	void GetInfo_Msg_1();

	///
	void GetInfo_Msg_2();

	///
	void GetObject_Data_1_Msg();

	///
	void GetObject_Data_Ctrl_Msg();

	///
	void GetPresence_Msg();

	///
	void GetRelay_Ctrl_Msg();

	///	
	void GetStatus_Msg();

	///
	void GetTime_Msg();

	///
	void GetTriggered_Obj_Msg();

	///
	void GetWrong_Dir_Msg();

	///
	void GetAll();
private:

	///��ǩ
	QLabel *RecAddress;
	QLabel *RecPort;

	///�༭����
	QLineEdit *RecPortLine;
	QLineEdit *RecAddressLine;

	///��ʾ����
	QTextEdit *ShowText_Info;
	QTextEdit *ShowText_Content;

	///����
	QPushButton *GetInfoButton;
	QPushButton *ConnectButton;
	QPushButton *RecButton;
	QPushButton *StopButton;
	QPushButton *Feature_Msg_1Button;
	QPushButton *Feature_Msg_2Button;
	QPushButton *Info_Msg_1Button;
	QPushButton *Info_Msg_2Button;
	QPushButton *Object_Data_1_MsgButton;
	QPushButton *Object_Data_Ctrl_MsgButton;
	QPushButton *Presence_MsgButton;
	QPushButton *Relay_Ctrl_MsgButton;	
	QPushButton *Status_MsgButton;
	QPushButton *Time_MsgButton;
	QPushButton *Triggered_Obj_MsgButton;
	QPushButton *Wrong_Dir_MsgButton;
	QPushButton *AllButton;

	///IP���˿��ַ���
	QString sRecAdd;
	QString nRecPort;
	QString PrintTmp;
	
	///ָ��Tcp���ָ��
	ClientRec *pRecData;

	
};

#endif
