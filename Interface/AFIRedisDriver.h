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

class AFIRedisDriver
{
public:
	virtual ~AFIRedisDriver() {}

    virtual bool connect(const std::string& ip, const uint16_t nPort = 6379, const std::string& auth = NULL_STR, const uint8_t db_index = 1) = 0;
    virtual bool reconnect() = 0;
    virtual bool enable() = 0;

	//virtual const std::string& GetIP() = 0;
	//virtual const int GetPort() = 0;
	//virtual const std::string&  GetAuthKey() = 0;

	virtual bool del(const std::string& strKey) = 0;
	virtual bool exists(const std::string& strKey) = 0;
	virtual bool expire(const std::string& strKey, unsigned int nSecs) = 0;
	virtual bool expireat(const std::string& strKey, int timestamp) = 0;

	///////////////////////////////////////////////////////////

	virtual const bool Set(const std::string& strKey, const std::string& strValue) = 0;
	virtual const bool Get(const std::string& strKey, std::string& strValue) = 0;

	///////////////////////////////////////////////////////////

	//SET if Not eXists
	virtual const bool SetNX(const std::string& strKey, const std::string& strValue) = 0;
	//set key->value and set Expire time
	virtual const bool SetEX(const std::string& strKey, const std::string& strValue, const unsigned int nSeconds) = 0;

	virtual const bool HSet(const std::string& strKey, const std::string& strField, const std::string& strValue) = 0;
	virtual const bool HGet(const std::string& strKey, const std::string& strField, std::string& strValue) = 0;
	virtual const bool HMSet(const std::string& strKey, const std::vector<std::string>& fieldVec, const std::vector<std::string>& valueVec) = 0;
	virtual const bool HMGet(const std::string& strKey, const std::vector<std::string>& fieldVec, std::vector<std::string>& valueVec) = 0;

	virtual const bool HExists(const std::string& strKey, const std::string& strField) = 0;
	virtual const bool HDel(const std::string& strKey, const std::string& strField) = 0;
	virtual const bool HLength(const std::string& strKey, int& nLen) = 0;

	virtual const bool HKeys(const std::string& strKey, std::vector<std::string>& fieldVec) = 0;
	virtual const bool HValues(const std::string& strKey, std::vector<std::string>& valueVec) = 0;
	virtual const bool HGetAll(const std::string& strKey, std::vector<std::pair<std::string, std::string> >& valueVec) = 0;



	virtual const bool ZAdd(const std::string& strKey, const double nScore, const std::string& strMember) = 0;
	virtual const bool ZIncrBy(const std::string& strKey, const std::string& strMember, const double dwIncrement) = 0;

	virtual const bool ZRem(const std::string& strKey, const std::string& strMember) = 0;
	virtual const bool ZRemRangeByRank(const std::string& strKey, const int nStart, const int nStop) = 0;
	virtual const bool ZRemRangeByScore(const std::string& strKey, const int nMin, const int nMax) = 0;


	virtual const bool ZScore(const std::string& strKey, const std::string& strMember, double& dwScore) = 0;
	virtual const bool ZRank(const std::string& strKey, const std::string& strMember, int& nRank) = 0;
	virtual const bool ZCard(const std::string& strKey, int& nCount) = 0;
	virtual const bool ZCount(const std::string& strKey, const int nMin, const int nMax, int& nCount) = 0;


	virtual const bool ZRevRange(const std::string& strKey, const int nStart, const int nStop, std::vector<std::pair<std::string, double> >& memberScoreVec) = 0;
	virtual const bool ZRevRank(const std::string& strKey, const std::string& strMember, int& nRank) = 0;
	virtual const bool ZRange(const std::string& strKey, const int nStartIndex, const int nEndIndex, std::vector<std::pair<std::string, double> >& memberScoreVec) = 0;
	virtual const bool ZRangeByScore(const std::string& strKey, const int nMin, const int nMax, std::vector<std::pair<std::string, double> >& memberScoreVec) = 0;

	///////////////////////////////////////////////////////////
	//push/pop form back of list
	//mpush. mpop
	virtual const bool ListPush(const std::string& strKey, const std::string& strValue) = 0;
	virtual const bool ListPop(const std::string& strKey, std::string& strValue) = 0;

	//>= star, < end
	virtual const bool ListRange(const std::string& strKey, const int nStar, const int nEnd, std::vector<std::string>& xList) = 0;
	virtual const bool ListLen(const std::string& strKey, int& nLength) = 0;

	virtual const bool ListIndex(const std::string& strKey, const int nIndex, std::string& strValue) = 0;
	virtual const bool ListRem(const std::string& strKey, const int nCount, const std::string& strValue) = 0;
	virtual const bool ListSet(const std::string& strKey, const int nCount, const std::string& strValue) = 0;
	virtual const bool ListTrim(const std::string& strKey, const int nStar, const int nEnd) = 0;
};