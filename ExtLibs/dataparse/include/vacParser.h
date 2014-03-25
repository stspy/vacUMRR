#ifndef VAC_PARSER_H
#define VAC_PARSER_H

#ifdef  VAC_API
#else
#define VAC_API _declspec(dllimport)
#endif
#include <windows.h>
#include "vacDataMatter.h"
#include "json.h"
#include "mysql.h"
#include "vacAlgorithm.h"

////////////////////////////////////////////////////////////////
/**
* @class vacDataPackage
* @brief 传感器Rs485数据解析类
*
* @ingroup vacDataPackage
*/
class vacDataPackage
{
public:
	bool Parse2Json(Json::Value&,vector<INT8U>::iterator&,vector<INT8U>::iterator&);
	bool DBInit(string user,string password,string database,string host="localhost",int port=3306);
	bool DBInsert();
private:
	bool RsConfirm();
	bool RsXorCheckSum();
	bool GetJsonObj(Json::Value&);
	///处理标识为0500的Rs485的消息的对象
	vac0500Data m_c0500Data;
	///处理标识为0501的Rs485的消息的对象
	vac0501Data m_c0501Data;
	///处理标识为0510的Rs485的消息组的对象
	vac0510ComboData m_vec0510Data;
	///处理标识为0782的Rs485的消息的对象
	vac0782Data m_c0782Data;
	///处理标识为0783的第一类Rs485的消息的对象
	vac0783P0Data m_c0783P0Data;
	///处理标识为0783的第二类Rs485的消息的对象
	vac0783P1Data m_c0783P1Data;
	///处理标识为0783为的第三类Rs485的消息的对象
	vac0783P14Data m_c0783P14Data;
	///处理标识为0784的Rs485的消息的对象
	vac0784Data m_c0784Data;
	///处理标识为0780的第一类Rs485的消息的对象
	vac0780P1Data m_c0780P1Data;
	///处理标识为0780的第二类Rs485的消息的对象
	vac0780P2Data m_c0780P2Data;
	///处理标识为0781的Rs485的消息组的对象
	vac0781ComboData m_c0781Data;
	///数据库句柄
	MYSQL m_sqlhandle;
	///指向当前处理的rs485消息的首字节
	vector<INT8U>::const_iterator m_itHeadOfRs;
	///指向当前处理的rs485消息的末字节的后一位
	vector<INT8U>::const_iterator m_itEndOfRs;
};

/**
* @class vacDataParser
* @brief 传感器数据解析类
*
* @ingroup vacDataParser
*/
class vacDataParser
{
public:
	vacDataParser():m_VecConnect(16),m_vecConnectTagIt(2,m_VecConnect.begin()),m_itCurrRs485BlkBeg(m_vecConnectTagIt.begin()),m_itCurrRs485BlkEnd(m_itCurrRs485BlkBeg+1)
	{
	}
	///数据库参数设置
	bool SetDataBasePara(string user,string password,string database,string host="localhost",int port=3306);
	//获得解析Json对象
	bool ReadJsonPackage(Json::Value& jsondata);
	int ParseDataPackage(vector<unsigned char>&);
private:
	bool FindAllTagInData();
	bool FindAllTagInConnect();
	void ConnectData();
	///一个Rs485数据包的解析对象
	vacDataPackage m_cDataPackage;
	///指向连接区的数据的指针
	vector<INT8U> m_VecConnect;
	///存储连接段中所有Rs485起始位迭代器
	vector<vector<INT8U>::iterator> m_vecConnectTagIt;
	///指向当前处理的Rs485数据包的首字节的迭代器
	vector<vector<INT8U>::iterator>::iterator m_itCurrRs485BlkBeg;
	///指向当前处理的Rs485数据包的末字节后一位的迭代器
	vector<vector<INT8U>::iterator>::iterator m_itCurrRs485BlkEnd;

};






#endif