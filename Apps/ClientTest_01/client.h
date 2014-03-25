/**
 * @file client.h
 * @brief
 * 客户端界面
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
 * @brief 客户端界面 
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
	
	///配置接收IP
	std::string GetRecAddr();

	///配置接收端口
	unsigned int GetRecPort();

	///显示信息
	void PrintInfo(std::string str);

signals:

private slots:
	///按键槽，对应各自按键功能
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

	///标签
	QLabel *RecAddress;
	QLabel *RecPort;

	///编辑窗口
	QLineEdit *RecPortLine;
	QLineEdit *RecAddressLine;

	///显示区域
	QTextEdit *ShowText_Info;
	QTextEdit *ShowText_Content;

	///按键
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

	///IP，端口字符串
	QString sRecAdd;
	QString nRecPort;
	QString PrintTmp;
	
	///指向Tcp类的指针
	ClientRec *pRecData;

	
};

#endif
