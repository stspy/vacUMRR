/**
 * @file server.h
 * @brief
 * ����������
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
 * @brief �������˽��� 
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

	///��ӡ��Ϣ
	void PrintInfo(std::string str);

signals:
	

private slots:
	
	///�����ۣ���Ӧ���԰�������
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
	///��ǩ
	QLabel *RecAddress;
	QLabel *RecPort;
	QLabel *SendAddress;
	QLabel *SendPort;
	QLabel *Host;
	QLabel *User;
	QLabel *Passwd;
	QLabel *DBname;
	QLabel *DBport;

	///�༭����
	QLineEdit *SendPortLine;
	QLineEdit *SendAddressLine;
	QLineEdit *RecPortLine;
	QLineEdit *RecAddressLine;
	QLineEdit *HostLine;
	QLineEdit *UserLine;
	QLineEdit *PasswdLine;
	QLineEdit *DBnameLine;
	QLineEdit *DBportLine;

	///��ʾ����
	QTextEdit *ShowText;

	///����
	QPushButton *ShowInfoButton;
	QPushButton *ConnectSrvButton;
	QPushButton *RecButton;
	QPushButton *StopRecButton;
	QPushButton *ListenCliButton;
	QPushButton *SendButton;
	QPushButton *StopSendButton;
	
	///���շ�������IP�Ͷ˿ں�
	QString sRecAdd;
	QString nRecPort;

	///���ص�IP�Ͷ˿ں�
	QString sSelfAdd;
	QString nSelfPort;
	QString PrintTmp;

	///���ݿ����
	QString sHost;
	QString sUser;
	QString sPasswd;
	QString sDBname;
	QString nDBport;


	///�ַ�������
	std::string sJson_to_Str;
	///ָ��Tcp���ָ��
	vacRecNetData *pRecNetdata;

	///Jsonд��ʽ
	Json::StyledWriter styled_writer;
	Json::FastWriter fast_writer;

	///���ݿ⽨����־
	int nflag_db;

	//�����ʹ���
	int nSend_Time;
};

#endif
