/**
 * @file vacDataMatter.h
 * @brief Can消息数据处理类
 * 
 * @see 
 *
 * @author Z. W. 
 * @version 0.1.0
 * @date 2014/03/09
 */
#ifndef VAC_DATA_MATTER_H
#define VAC_DATA_MATTER_H
#include <windows.h>
#include "mysql.h"
#include "json.h"
#include "vacRadarCommon.h"
#include <string>
#include <vector>
using namespace std;

/**
* @class vacBaseDBMatter
* @brief Can消息数据处理的虚基类
*
*
* @ingroup DBMatter
*/
class vacBaseDBMatter
{
public:
	vacBaseDBMatter()
	{}
	virtual ~vacBaseDBMatter()
	{}
	virtual bool Assign(vector<INT8U>::const_iterator& it)
	{
		return false;
	}
	virtual Json::Value& GetJson() =0;
	virtual bool DBInsert(MYSQL&)
	{
		return false;
	}
	static string m_systime;//当前系统时间
	static int m_timestamp;//当前时间戳
private:
};

/**
* @class vac0510Data
* @brief 以0x0510为标识的Can消息数据处理类
*
* @ingroup DBMatter
*/
class  vac0510Data:vacBaseDBMatter
{
public:
	vac0510Data()
	{}
	vac0510Data(vector<INT8U>::const_iterator& it);
	vac0510Data(const vac0510Data& objInfo)
	{
		*this=objInfo;
	}
	bool Assign(vector<INT8U>::const_iterator& it);
	vac0510Data& operator=(const vac0510Data& objInfo)
	{
		m_nObjLen=objInfo.m_nObjLen;
		m_nObjXPos=objInfo.m_nObjXPos;
		m_nObjYPos=objInfo.m_nObjYPos;
		m_nObjXVelo=objInfo.m_nObjXVelo;
		m_nObjYVelo=objInfo.m_nObjYVelo;
		m_nObjId=objInfo.m_nObjId;
		return *this;
	}
	Json::Value& GetJson();
	bool DBInsert(MYSQL&);
	/**
	* @brief 获得目标ID
	* 
	* @param None
	*						
	* @return int:目标ID
	*/
	int GetID()
	{
		return m_nObjId;
	}
private:
	///目标ID
	int m_nObjId;
	///x轴位置
	int m_nObjXPos;
	///y轴位置
	int m_nObjYPos;
	///x轴速度
	int m_nObjXVelo;
	///y轴速度
	int m_nObjYVelo;
	///目标长度
	int m_nObjLen;
	///解析后的Json对象
	Json::Value m_JsonObjInfo;
};

/**
* @class vac0500Data
* @brief 以0x0500为标识的Can消息数据处理类
*
* @ingroup DBMatter
*/
class  vac0500Data:vacBaseDBMatter
{
public:
	vac0500Data():m_bDBUpdate(false)
	{}
	vac0500Data(vector<INT8U>::const_iterator& it);
	bool Assign(vector<INT8U>::const_iterator& it);
	Json::Value& GetJson();
	bool DBInsert(MYSQL&);
/**
* @brief 获得目标ID
* 
* @param None
*						
* @return int:目标ID
*/
	bool isDBChange()
	{
		return m_bDBUpdate;
	}
private:
	int m_nSensorID;
	bool m_bInterference;
	bool m_bError_Flag;
	INT32U m_nTimeStampRcv;
	Json::Value m_JsonObjInfo;
	bool m_bDBUpdate;//数据库待更新的标识位
};

/**
* @class vac0501Data
* @brief 以0x0501为标识的Can消息数据处理类
*
* @ingroup DBMatter
*/
class vac0501Data:vacBaseDBMatter
{
public:
	vac0501Data()
	{}
	vac0501Data(vector<INT8U>::const_iterator& it);
	bool Assign(vector<INT8U>::const_iterator& it);
	Json::Value& GetJson();
	int GetTotalObjMsg()
	{
		return m_nNumberOfMsg*m_nNumberOfObj;
	}
private:
	int m_nNumberOfObj;
	int m_nNumberOfMsg;
	int m_nCycleCount;
	int m_nCycleDuration;
	Json::Value m_JsonObjInfo;
};

class vac0781ComboData;

/**
* @class 0780P1Data
* @brief 以0x0789为标识的Can消息数据的第一类消息处理类
*
* @ingroup DBMatter
*/
class vac0780P1Data:vacBaseDBMatter
{
public:
	vac0780P1Data():m_bLane_Direction(8),m_bAssignFlag(0),m_bDBUpdate(false),m_nNumberOfClasses(0)
	{}
	vac0780P1Data(vector<INT8U>::const_iterator& it);
	bool Assign(vector<INT8U>::const_iterator& it);
	Json::Value& GetJson();
/**
* @brief 消息是否已获取
* 
* @param None
*						
* @return bool:消息获取成功返回true，失败返回false
*/
	bool isReady()
	{
		return m_bAssignFlag;
	}
/**
* @brief 获得系统当前返回数据中feature消息的总数
* 
*  按照说明文档应该使用m_nNumberOfmLines*m_nNumberOfClasses*m_nNumberOfLanes，但实际数据分析后与文档不一致
* @param None
*						
* @return int:feature消息的总数
*/
	int GetTotalFeatureNumber()
	{
		return /*m_nNumberOfmLines**/m_nNumberOfClasses*m_nNumberOfLanes;//
	}
	bool DBInsert(MYSQL&);
/**
* @brief 获得数据图当前是否需要更新
* 
* @param None
*						
* @return bool：需要更新返回true，不需要返回false
*/
	bool isDBChage()
	{
		return m_bDBUpdate;
	}
	friend class vac0781ComboData;
private:
	static int m_nTotalFeatureNumber;
	int m_nNumberOfmLines;
	int m_nNumberOfLanes;
	int m_nNumberOfClasses;
	int m_nStatusBits;
	vector<bool> m_bLane_Direction;
	int m_nActive_features;
	int m_nInterval_Time;
	int m_nSensor_ID;
	//int m_Stuff_Bits;
	Json::Value m_JsonObjInfo;//返回的json对象
	bool m_bAssignFlag;
	bool m_bDBUpdate;
};

/**
* @class 0780P2Data
* @brief 以0x0789为标识的Can消息数据的第二类消息处理类
*
* @ingroup DBMatter
*/
class vac0780P2Data:vacBaseDBMatter
{
public:
	vac0780P2Data():m_bAssignFlag(false)
	{}
	vac0780P2Data(vector<INT8U>::const_iterator& it);
	bool Assign(vector<INT8U>::const_iterator& it);
	Json::Value& GetJson();
/**
* @brief 数据解析是否完成
* 
* @param None
*						
* @return bool：解析完成返回true，否则返回false
*/	
	bool isReady()
	{
		return m_bAssignFlag;
	}
private:
	INT32U m_nUSec;
	INT32U m_nSec;
	Json::Value m_JsonObjInfo;
	bool m_bAssignFlag;//解析是否成功标识位
};

/**
* @class vac0781P1Data
* @brief 以0x0781为标识的Can消息数据的第一类消息处理类
*
* @ingroup DBMatter
*/
class vac0781P1Data:vacBaseDBMatter
{
public:
	vac0781P1Data()
	{}
	vac0781P1Data(vector<INT8U>::const_iterator& it);
	bool Assign(vector<INT8U>::const_iterator& it);
	Json::Value& GetJson();
private:
	int m_nMsgNumber;
	int m_nMeasure_Line;
	int m_nLane;
	int m_nHeadway;
	int m_nVehicleClass;
	int m_nPercentile85_Speed;
	int m_nAvSpeed;
	Json::Value m_JsonObjInfo;
};

/**
* @class vac0781P2Data
* @brief 以0x0781为标识的Can消息数据的第二类消息处理类
*
* @ingroup DBMatter
*/
class vac0781P2Data:vacBaseDBMatter
{
public:
	vac0781P2Data()
	{}
	vac0781P2Data(vector<INT8U>::const_iterator& it);
	bool Assign(vector<INT8U>::const_iterator& it);
	Json::Value& GetJson();
private:

	int m_nMsgNumber;
	int m_nMeasure_Line;
	int m_nLane;
	int m_nGap;
	int m_nVehicleClass;
	int m_nVolume;
	int m_nOccupancy;
	Json::Value m_JsonObjInfo;
};

/**
* @class vac0782Data
* @brief 以0x0782为标识的Can消息数据的消息处理类
*
* @ingroup DBMatter
*/
class vac0782Data:vacBaseDBMatter
{
public:
	vac0782Data()
	{}
	vac0782Data(vector<INT8U>::const_iterator& it);
	bool Assign(vector<INT8U>::const_iterator& it);
	Json::Value& GetJson();
	bool DBInsert(MYSQL&);
/**
* @brief 获得数据图当前是否需要更新
* 
* @param None
*						
* @return bool：需要更新返回true，不需要返回false
*/
	bool isDBChage()
	{
		return m_bDBUpdate;
	}
private:
	int m_nSensor_ID;
	int m_nIntervalCountdown;
	int m_nNumberOfLanes;
	int m_nSerialNumber;
	Json::Value m_JsonObjInfo;
	bool m_bDBUpdate;
};

/**
* @class vac0783P0Data
* @brief 以0x0783为标识的Can消息数据的第一类消息处理类
*
* @ingroup DBMatter
*/
class vac0783P0Data:vacBaseDBMatter
{
public:
	vac0783P0Data():m_vecPresence_Msg(40)
	{}
	vac0783P0Data(vector<INT8U>::const_iterator& it);
	bool Assign(vector<INT8U>::const_iterator& it);
	Json::Value& GetJson();
	bool DBInsert(MYSQL& sqlhandle);
private:
	int m_nMeasure_Line;
	vector<bool> m_vecPresence_Msg;
	Json::Value m_JsonObjInfo;
	bool m_bDBUpdate;
};

/**
* @class vac0783P1Data
* @brief 以0x0783为标识的Can消息数据的第二类消息处理类
*
* @ingroup DBMatter
*/
class vac0783P1Data:vacBaseDBMatter
{
public:
	vac0783P1Data():m_vecWrongDir_Msg(8)
	{}
	vac0783P1Data(vector<INT8U>::const_iterator& it);
	bool Assign(vector<INT8U>::const_iterator& it);
	Json::Value& GetJson();
	bool DBInsert(MYSQL& sqlhandle);
private:
	int m_nMeasure_Line;
	vector<bool> m_vecWrongDir_Msg;
	Json::Value m_JsonObjInfo;
	bool m_bDBUpdate;
};

/**
* @class vac0783P1Data
* @brief 以0x0783为标识的Can消息数据的第三类消息处理类
*
* @ingroup DBMatter
*/
class vac0783P14Data:vacBaseDBMatter
{
public:
	vac0783P14Data():m_vecRelay(16),m_vecRelayAssignment(16)
	{}
	vac0783P14Data(vector<INT8U>::const_iterator& it);
	bool Assign(vector<INT8U>::const_iterator& it);
	Json::Value& GetJson();
private:
	int m_nNetWorkID;
	//int m_nMeasure_Line;
	vector<bool> m_vecRelay;
	vector<bool> m_vecRelayAssignment;
	Json::Value m_JsonObjInfo;
};

/**
* @class vac0784Data
* @brief 以0x0784为标识的Can消息数据的消息处理类
*
* @ingroup DBMatter
*/
class vac0784Data:vacBaseDBMatter
{
public:
	vac0784Data():m_bAssignFlag(false)
	{}
	vac0784Data(vector<INT8U>::const_iterator& it);
	bool Assign(vector<INT8U>::const_iterator& it);
	Json::Value& GetJson();
	bool DBInsert(MYSQL& sqlhandle);
/**
* @brief 获得当前数据解析是否成功
* 
* @param None
*						
* @return bool：成功返回true，不成功返回false
*/
	bool isReady()
	{
		return m_bAssignFlag;
	}
/**
* @brief 获得中继触发所对应的目标编号
* 
* @param None
*						
* @return vector<int>&：返回所有目标编号的vector
*/
	vector<int>& GetObjID()
	{
		return m_vecObjID;
	}
private:
	int m_nActivatedRelayNumber;
	int m_nMessageNumber;
	int m_nNumberOfTriggeredObj;
	vector<int> m_vecObjID;
	Json::Value m_JsonObjInfo;
	bool m_bAssignFlag;
};

/**
* @class vac0781ComboData
* @brief 以0x0781为标识的Can消息数据的消息组合处理类
*
* @ingroup DBMatter
*/
class vac0781ComboData:vacBaseDBMatter
{
public:
	vac0781ComboData():m_bAssginComplete(false)
	{}
	vac0781ComboData(vector<INT8U>::const_iterator& it);
	bool Assign(vector<INT8U>::const_iterator& it);
	Json::Value& GetJson();
/**
* @brief 获得当前数据解析是否成功
* 
* @param None
*						
* @return bool：成功返回true，不成功返回false
*/
	bool isReady()
	{
		return m_bAssginComplete;
	}
private:
	bool m_bAssginComplete;
	vector<vac0781P1Data> m_vec0781P1Data;
	vector<vac0781P2Data> m_vec0781P2Data;
	Json::Value m_JsonObjInfo;
};

/**
* @class vac0510ComboData
* @brief 以0x0781为标识的Can消息数据的消息组合处理类
*
* @ingroup DBMatter
*/
class vac0510ComboData:vacBaseDBMatter
{
public:
	vac0510ComboData():m_bAssignFlag(false)
	{}
	vac0510ComboData(vector<INT8U>::const_iterator& it,int totalnumber);
	bool Assign(vector<INT8U>::const_iterator& it,int totalnumber);
	Json::Value& GetJson();
	bool DBInsert(MYSQL&,vector<int>&);
private:
	vector<vac0510Data> m_vec0510Data;
	Json::Value m_JsonObjInfo;
	bool m_bAssignFlag;
};
#endif