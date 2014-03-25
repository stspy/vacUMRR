/**
 * @file vacAlgorithem.h
 * @brief 基本算法
 * 
 * @see 
 *
 * @author Z. W. 
 * @version 0.1.0
 * @date 2014/03/09
 */
#ifndef VAC_ALGORITHEM_H
#define VAC_ALGORITHEM_H

#include "vacRadarCommon.h"
#include <vector>
using namespace std;

/**
 * @brief 不同长度的整型与迭代器对应位置的值相互比较的函数模板
 *
 * @param cByteIt: 迭代器所指向的位置
 * @param counterpart： 比较值
 *						
 * @return bool：相等返回ture，不相等返回false
 */
template<typename T>
bool BitsComparer(const vector<INT8U>::const_iterator& cByteIt,T counterpart)
{
	int nLen=sizeof(counterpart);
	int nComposedBits=0;
	for (int i=0;i<nLen;i++)
	{
		nComposedBits+=*(cByteIt+i)<<(8*i);
	}
	return !(nComposedBits^counterpart);
}

/**
 * @brief 不同长度的整型与迭代器对应位置的值相互比较的函数模板
 *
 *带有迭代器使用安全检查的重载版本
 *
 * @param cByteIt: 迭代器所指向的位置
 * @param counterpart： 比较值
 *						
 * @return bool：相等返回ture，不相等返回false
 */
template<typename T>
bool BitsComparer(const vector<INT8U>::const_iterator cByteIt,const vector<INT8U>::const_iterator cByteItEnd,T counterpart)
{
	int nLen=sizeof(counterpart);
	int nComposedBits=0;
	if (cByteItEnd-cByteIt<nLen)
	{
		return 0;
	}
	for (int i=0;i<nLen;i++)
	{
		nComposedBits+=*(cByteIt+i)<<(8*i);
	}
	return !(nComposedBits^counterpart);
}

vector<INT8U>::iterator  TagFind(vector<INT8U>::iterator begin,vector<INT8U>::iterator ItEnd,INT32U tag);
bool TypeConfirm(vector<INT8U>::const_iterator,INT16U tag1,INT16U tag2,INT16U tag3,INT16U tag4);
bool TypeConfirm(vector<INT8U>::const_iterator,INT16U tag1,INT16U tag2,INT16U tag3,INT16U tag4,int diff);
INT16U GetINT16U(const vector<INT8U>::const_iterator cByteIt);
INT32U GetINT32U(const vector<INT8U>::const_iterator cByteIt);
INT16U GetReverseINT16U(const vector<INT8U>::const_iterator cByteIt);
INT32U GetReverseINT32U(const vector<INT8U>::const_iterator cByteIt);
#endif
