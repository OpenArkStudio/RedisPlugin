/*
* This source file is part of ArkGameFrame
* For the latest info, see https://github.com/ArkGame
*
* Copyright (c) 2013-2017 ArkGame authors.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
*/

#pragma once

#include "aredis/aredis.hpp"
#include "Interface/AFIRedisModule.h"

class  AFCRedisDriver : public AFIRedisDriver
{
public:
    AFCRedisDriver();
    virtual ~AFCRedisDriver();

    virtual bool connect(const std::string& ip, const uint16_t nPort = 6379, const std::string& auth = NULL_STR, const uint8_t db_index = 1);
    virtual bool enable();

	//virtual const std::string& GetIP();
	//virtual const int GetPort();
	//virtual const std::string&  GetAuthKey();

	virtual bool del(const std::string& strKey);
	virtual bool exists(const std::string& strKey);
	virtual bool expire(const std::string& strKey, uint32_t seconds);
	virtual bool expireat(const std::string& strKey, int timestamp);

	///////////////////////////////////////////////////////////

	virtual bool set(const std::string& strKey, const std::string& strValue);
	virtual bool Get(const std::string& strKey, std::string& strValue);

	///////////////////////////////////////////////////////////

	//SET if Not eXists
	virtual bool SetNX(const std::string& strKey, const std::string& strValue);
	//set key->value and set Expire time
	virtual bool SetEX(const std::string& strKey, const std::string& strValue, const unsigned int nSeconds);

    virtual bool HSet(const std::string& strKey, const std::string& strField, const std::string& strValue);
    virtual bool HGet(const std::string& strKey, const std::string& strField, std::string& strValue);
    virtual bool HMSet(const std::string& strKey, const std::vector<std::string>& fieldVec, const std::vector<std::string>& valueVec);
    virtual bool HMGet(const std::string& strKey, const std::vector<std::string>& fieldVec, std::vector<std::string>& valueVec);

    virtual bool HExists(const std::string& strKey, const std::string& strField);
    virtual bool HDel(const std::string& strKey, const std::string& strField);
    virtual bool HLength(const std::string& strKey, int& nLen);

    virtual bool HKeys(const std::string& strKey, std::vector<std::string>& fieldVec);
    virtual bool HValues(const std::string& strKey, std::vector<std::string>& valueVec);
    virtual bool HGetAll(const std::string& strKey, std::vector<std::pair<std::string, std::string> >& valueVec);

	///////////////默认：大到小排序 ////////////////////////////////////////////
	// sorted set系列
	virtual bool ZAdd(const std::string& strKey, const double nScore, const std::string& strData);
	virtual bool ZIncrBy(const std::string& strKey, const std::string& strMember, const double nIncrement);
	// 移除key中的成员member
    virtual bool ZRem(const std::string& strKey, const std::string& strMember);
    virtual bool ZRemRangeByRank(const std::string& strKey, const int nStart, const int nStop);
    virtual bool ZRemRangeByScore(const std::string& strKey, const int nMin, const int nMax);

	// 返回有序集 key 中，成员 member 的 score 值
	virtual const bool ZScore(const std::string& strKey, const std::string& strMember, double& nScore);

	//累count.得到个数
	virtual bool ZCard(const std::string& strKey, int& nCount);
	// score 值在 min 和 max 之间的成员的数量
	virtual bool ZCount(const std::string& strKey, const int nMin, const int nMax, int& nCount);

	// 返回key中指定区间内的成员, 包含分数:大到小排序
    virtual bool ZRevRange(const std::string& strKey, const int nStart, const int nStop, std::vector<std::pair<std::string, double> >& memberScoreVec);
    virtual bool ZRevRank(const std::string& strKey, const std::string& strMember, int& nRank);
    virtual bool ZRangeByScore(const std::string& strKey, const int nMin, const int nMax, std::vector<std::pair<std::string, double> >& memberScoreVec);

	///////////////////////////////////////////////////////////
	//push form back of the list
	//pop form head of the list
    virtual bool ListPush(const std::string& strKey, const std::string& strValue);
    virtual bool ListPop(const std::string& strKey, std::string& strValue);

	//>= nStart, < end
    virtual bool ListRange(const std::string& strKey, const int nStart, const int nEnd, std::vector<std::string>& xList);
    virtual bool ListLen(const std::string& strKey, int& nLength);

    virtual bool ListIndex(const std::string& strKey, const int nIndex, std::string& strValue);
    virtual bool ListRem(const std::string& strKey, const int nCount, const std::string& strValue);
    virtual bool ListSet(const std::string& strKey, const int nCount, const std::string& strValue);
    virtual bool ListTrim(const std::string& strKey, const int nStar, const int nEnd);

private:
	bool mbEnable;
    ARK_SHARE_PTR<aredis::redis_conn> m_pRedisClient;
};