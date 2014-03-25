/**
 * @file server.h
 * @brief
 * 服务器界面
 *
 * @see server
 *
 * @author N. W. J.
 * @version 0.1.0
 * @date 2014/02/26
 */

#ifndef SERVER_H
#define SERVER_H

#include <QDialog>
#include <QtGui>
#include "vacNetSend.h"
#include "vacParser.h"
#include "vacRadarCommon.h"

class QCheckBox;
class QLabel;
class QLineEdit;
class QPushButton;


/** 
 * @class vacServerDialog
 * @brief 服务器端界面 
 * 
 *
 * @ingroup vacServerDialog
 */
class vacServerDialog : public QDialog
{
	Q_OBJECT
public:
	///
	vacServerDialog(QWidget *parent = 0);

	///打印信息
	void PrintInfo(std::string str);

signals:
	

private slots:
	
	///按键槽，对应各自按键功能
	void GetIPInfo();
	
	///
	void ConnectSever();

	///
	void RecFile();

	///
	void StopRec();

	///
	void ListenClient();

	///
	void SendFile();

	///
	void StopSend();

private:
	///标签
	QLabel *RecAddress;
	QLabel *RecPort;
	QLabel *SendAddress;
	QLabel *SendPort;
	QLabel *Host;
	QLabel *User;
	QLabel *Passwd;
	QLabel *DBname;
	QLabel *DBport;

	///编辑窗口
	QLineEdit *SendPortLine;
	QLineEdit *SendAddressLine;
	QLineEdit *RecPortLine;
	QLineEdit *RecAddressLine;
	QLineEdit *HostLine;
	QLineEdit *UserLine;
	QLineEdit *PasswdLine;
	QLineEdit *DBnameLine;
	QLineEdit *DBportLine;

	///显示区域
	QTextEdit *ShowText;

	///按键
	QPushButton *ShowInfoButton;
	QPushButton *ConnectSrvButton;
	QPushButton *RecButton;
	QPushButton *StopRecButton;
	QPushButton *ListenCliButton;
	QPushButton *SendButton;
	QPushButton *StopSendButton;
	
	///接收服务器的IP和端口号
	QString sRecAdd;
	QString nRecPort;

	///本地的IP和端口号
	QString sSelfAdd;
	QString nSelfPort;
	QString PrintTmp;

	///数据库变量
	QString sHost;
	QString sUser;
	QString sPasswd;
	QString sDBname;
	QString nDBport;


	///字符串变量
	std::string sJson_to_Str;
	///指向Tcp类的指针
	vacRecNetData *pRecNetdata;

	///Json写格式
	Json::StyledWriter styled_writer;
	Json::FastWriter fast_writer;

	///数据库建立标志
	int nflag_db;

	//发送送次数
	int nSend_Time;
};

#endif
