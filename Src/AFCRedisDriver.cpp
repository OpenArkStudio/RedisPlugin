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

#include "AFCRedisDriver.h"

#define  REDIS_CATCH(function, line) catch(redis::connection_error er)\
{\
    mbEnable = false;\
    std::cout<< "Redis Error:"<< er.what() << " Function:" << function << " Line:" << line << std::endl;\
    return false;\
}\
catch(redis::timeout_error er)\
{\
    mbEnable = false;\
    std::cout<< "Redis Error:"<< er.what() << " Function:" << function << " Line:" << line << std::endl;\
    return false;\
}\
catch(redis::protocol_error er)\
{\
    std::cout<< "Redis Error:"<< er.what() << " Function:" << function << " Line:" << line << std::endl;\
    return false;\
}\
catch(redis::key_error er)\
{\
    std::cout<< "Redis Error:"<< er.what() << " Function:" << function << " Line:" << line << std::endl;\
    return false;\
}\
catch(redis::value_error er)\
{\
    std::cout<< "Redis Error:"<< er.what() << " Function:" << function << " Line:" << line << std::endl;\
    return false;\
}\
catch (...)\
{\
return false; \
}

AFCRedisDriver::AFCRedisDriver()
{
	mbEnable = false;
	m_pRedisClient = nullptr;
}

AFCRedisDriver::~AFCRedisDriver()
{

}

bool AFCRedisDriver::connect(const std::string& ip, const uint16_t port/* = 6379*/, const std::string& auth/* = NULL_STR*/, const uint8_t db_index/* = 1*/)
{
	try
	{
		if (m_pRedisClient != nullptr)
		{
            m_pRedisClient.reset();
		}

        m_pRedisClient = std::make_shared<aredis::redis_conn>();
        if (m_pRedisClient->connect(ip.c_str(), port, auth.c_str(), db_index))
        {
            mbEnable = true;
        }
	}
	catch (...)
	{
		mbEnable = false;
	}

	return mbEnable;
}

bool AFCRedisDriver::enable()
{
	return mbEnable;
}

//const std::string & AFCRedisDriver::GetIP()
//{
//	//TODO
//	return NULL_STR;
//}
//
//int AFCRedisDriver::GetPort()
//{
//	return 0;
//}
//
//const std::string & AFCRedisDriver::GetAuthKey()
//{
//    //TODO
//	return NULL_STR;
//}

bool AFCRedisDriver::del(const std::string & strKey)
{
	if (!enable())
	{
		return false;
	}

    aredis::redis_command cmd;
    cmd.cmd("DEL", strKey);
    m_pRedisClient->command(cmd);
    aredis::resp_result result;
    return m_pRedisClient->reply(result);
}

bool AFCRedisDriver::exists(const std::string & strKey)
{
	if (!enable())
	{
		return false;
	}

    aredis::redis_command cmd;
    cmd.cmd("EXISTS", strKey);
    m_pRedisClient->command(cmd);
    aredis::resp_result result;
    return m_pRedisClient->reply(result);
}

bool AFCRedisDriver::expire(const std::string & strKey, uint32_t seconds)
{
	if (!enable())
	{
		return false;
	}

    aredis::redis_command cmd;
    cmd.cmd("EXPIRE", strKey, seconds);
    m_pRedisClient->command(cmd);
    aredis::resp_result result;
    return m_pRedisClient->reply(result);
}

bool AFCRedisDriver::expireat(const std::string& strKey, int timestamp)
{
    if (!enable())
    {
        return false;
    }

    aredis::redis_command cmd;
    cmd.cmd("EXPIREAT", strKey, timestamp);
    m_pRedisClient->command(cmd);
    aredis::resp_result result;
    return m_pRedisClient->reply(result);
}

bool AFCRedisDriver::set(const std::string& strKey, const std::string& strValue)
{
	if (!enable())
	{
		return false;
	}

    aredis::redis_command cmd;
    cmd.cmd("SET", strKey, strValue);
    m_pRedisClient->command(cmd);
    aredis::resp_result result;
    return m_pRedisClient->reply(result);
}

bool AFCRedisDriver::Get(const std::string & strKey, std::string & strValue)
{
	if (!enable())
	{
		return false;
	}

    aredis::redis_command cmd;
    cmd.cmd("GET", strKey, strValue);
    m_pRedisClient->command(cmd);
    aredis::resp_result result;
    if (m_pRedisClient->reply(result))
    {
        strValue = result.dump();
        return true;
    }

    return false;
}

bool AFCRedisDriver::SetNX(const std::string & strKey, const std::string & strValue)
{
	if (!enable())
	{
		return false;
	}

	try
	{
		return m_pNoSqlClient->setnx(strKey, strValue);
	}
	REDIS_CATCH(__FUNCTION__, __LINE__);

	return false;
}

bool AFCRedisDriver::SetEX(const std::string & strKey, const std::string & strValue, const unsigned int nSeconds)
{
	if (!enable())
	{
		return false;
	}

	try
	{
		m_pNoSqlClient->setex(strKey, strValue, nSeconds);
		return true;
	}
	REDIS_CATCH(__FUNCTION__, __LINE__);

	return false;
}

bool AFCRedisDriver::HSet(const std::string & strKey, const std::string & strField, const std::string & strValue)
{
	if (!enable())
	{
		return false;
	}

	if (strKey.empty() || strField.empty())
	{
		return false;
	}
	try
	{
		m_pNoSqlClient->hset(strKey, strField, strValue);
		return true;
	}
	REDIS_CATCH(__FUNCTION__, __LINE__);

	return false;
}

bool AFCRedisDriver::HGet(const std::string & strKey, const std::string & strField, std::string & strValue)
{
	if (!enable())
	{
		return false;
	}

	try
	{
		strValue = m_pNoSqlClient->hget(strKey, strField);
		return true;
	}
	REDIS_CATCH(__FUNCTION__, __LINE__);
	return false;
}

bool AFCRedisDriver::HMSet(const std::string & strKey, const std::vector<std::string>& fieldVec, const std::vector<std::string>& valueVec)
{
	if (!enable())
	{
		return false;
	}

	if (strKey.empty() <= 0 || fieldVec.size() != valueVec.size())
	{
		return false;
	}

	try
	{
		m_pNoSqlClient->hmset(strKey, fieldVec, valueVec);
		return true;
	}
	REDIS_CATCH(__FUNCTION__, __LINE__);

	return false;
}

bool AFCRedisDriver::HMGet(const std::string & strKey, const std::vector<std::string>& fieldVec, std::vector<std::string>& valueVec)
{
	if (!enable())
	{
		return false;
	}

	try
	{
		m_pNoSqlClient->hmget(strKey, fieldVec, valueVec);

		return fieldVec.size() == valueVec.size();
	}
	REDIS_CATCH(__FUNCTION__, __LINE__);


	return false;
}

bool AFCRedisDriver::HExists(const std::string & strKey, const std::string & strField)
{
	if (!enable())
	{
		return false;
	}

	try
	{
		return m_pNoSqlClient->hexists(strKey, strField);
	}
	REDIS_CATCH(__FUNCTION__, __LINE__);

	return false;
}

bool AFCRedisDriver::HDel(const std::string & strKey, const std::string & strField)
{
	if (!enable())
	{
		return false;
	}

	try
	{
		return m_pNoSqlClient->hdel(strKey, strField);
	}

	REDIS_CATCH(__FUNCTION__, __LINE__);

	return false;
}

bool AFCRedisDriver::HLength(const std::string & strKey, int & nLen)
{
	if (!enable())
	{
		return false;
	}

	try
	{
		nLen = m_pNoSqlClient->hlen(strKey);
		return true;
	}
	REDIS_CATCH(__FUNCTION__, __LINE__);
	return false;
}

bool AFCRedisDriver::HKeys(const std::string & strKey, std::vector<std::string>& fieldVec)
{
	if (!enable())
	{
		return false;
	}

	try
	{
		m_pNoSqlClient->hkeys(strKey, fieldVec);
		return true;
	}
	REDIS_CATCH(__FUNCTION__, __LINE__);

	return false;
}

bool AFCRedisDriver::HValues(const std::string & strKey, std::vector<std::string>& valueVec)
{
	if (!enable())
	{
		return false;
	}

	try
	{
		m_pNoSqlClient->hvals(strKey, valueVec);
		return true;
	}
	REDIS_CATCH(__FUNCTION__, __LINE__);

	return false;
}

bool AFCRedisDriver::HGetAll(const std::string & strKey, std::vector<std::pair<std::string, std::string>>& valueVec)
{
	if (!enable())
	{
		return false;
	}

	try
	{
		m_pNoSqlClient->hgetall(strKey, valueVec);
		return true;
	}
	REDIS_CATCH(__FUNCTION__, __LINE__);
	return false;
}

bool AFCRedisDriver::ZAdd(const std::string & strKey, const double nScore, const std::string & strData)
{
	if (!enable())
	{
		return false;
	}

	try
	{
		m_pNoSqlClient->zadd(strKey, nScore, strData);
		return true;
	}
	REDIS_CATCH(__FUNCTION__, __LINE__);

	return false;
}

bool AFCRedisDriver::ZIncrBy(const std::string & strKey, const std::string & strMember, const double nIncrement)
{
	if (!enable())
	{
		return false;
	}

	try
	{
		m_pNoSqlClient->zincrby(strKey, strMember, nIncrement);
		return true;
	}
	REDIS_CATCH(__FUNCTION__, __LINE__);

	return false;
}

bool AFCRedisDriver::ZRem(const std::string & strKey, const std::string & strMember)
{
	if (!enable())
	{
		return false;
	}

	try
	{
		m_pNoSqlClient->zrem(strKey, strMember);
		return true;
	}
	REDIS_CATCH(__FUNCTION__, __LINE__);

	return false;
}

bool AFCRedisDriver::ZRemRangeByRank(const std::string & strKey, const int nStart, const int nStop)
{
	if (!enable())
	{
		return false;
	}

	try
	{
		m_pNoSqlClient->zremrangebyrank(strKey, nStart, nStop);
		return true;
	}
	REDIS_CATCH(__FUNCTION__, __LINE__);
	return false;
}

bool AFCRedisDriver::ZRemRangeByScore(const std::string & strKey, const int nMin, const int nMax)
{
	if (!enable())
	{
		return false;
	}

	try
	{
		m_pNoSqlClient->zremrangebyscore(strKey, nMin, nMax);
		return true;
	}
	REDIS_CATCH(__FUNCTION__, __LINE__);
	return false;
}

bool AFCRedisDriver::ZScore(const std::string & strKey, const std::string & strMember, double & nScore)
{
	if (!enable())
	{
		return false;
	}

	try
	{
		nScore = m_pNoSqlClient->zscore(strKey, strMember);
		return true;
	}
	REDIS_CATCH(__FUNCTION__, __LINE__);
	return false;
}

bool AFCRedisDriver::ZCard(const std::string & strKey, int & nCount)
{
	if (!enable())
	{
		return false;
	}

	try
	{
		nCount = m_pNoSqlClient->zcard(strKey);
		return true;
	}
	REDIS_CATCH(__FUNCTION__, __LINE__);
	return false;
}

bool AFCRedisDriver::ZCount(const std::string & strKey, const int nMin, const int nMax, int & nCount)
{
	if (!enable())
	{
		return false;
	}

	try
	{
		nCount = m_pNoSqlClient->zcount(strKey, nMin, nMax);
		return true;
	}
	REDIS_CATCH(__FUNCTION__, __LINE__);

	return false;
}

bool AFCRedisDriver::ZRevRange(const std::string & strKey, const int nStart, const int nStop, std::vector<std::pair<std::string, double>>& memberScoreVec)
{
	if (!enable())
	{
		return false;
	}

	try
	{
		m_pNoSqlClient->zrevrange(strKey, nStart, nStop, memberScoreVec);
		return true;

	}
	REDIS_CATCH(__FUNCTION__, __LINE__);

	return false;
}

bool AFCRedisDriver::ZRangeByScore(const std::string & strKey, const int nMin, const int nMax, std::vector<std::pair<std::string, double>>& memberScoreVec)
{
	if (!enable())
	{
		return false;
	}

	try
	{
		m_pNoSqlClient->zrangebyscore(strKey, (double)nMin, (double)nMax, memberScoreVec);
		return true;
	}
	REDIS_CATCH(__FUNCTION__, __LINE__);

	return false;
}

bool AFCRedisDriver::ZRevRank(const std::string & strKey, const std::string & strMember, int & nRank)
{
	if (!enable())
	{
		return false;
	}

	try
	{
		nRank = m_pNoSqlClient->zrevrank(strKey, strMember);
		return true;
	}
	REDIS_CATCH(__FUNCTION__, __LINE__);

	return false;
}

bool AFCRedisDriver::ListPush(const std::string & strKey, const std::string & strValue)
{
	if (!enable())
	{
		return false;
	}
	try
	{

		m_pNoSqlClient->rpush(strKey, strValue);
		return true;

	}
	REDIS_CATCH(__FUNCTION__, __LINE__);

	return false;
}

bool AFCRedisDriver::ListPop(const std::string & strKey, std::string & strValue)
{
	if (!enable())
	{
		return false;
	}

	try
	{

		strValue = m_pNoSqlClient->rpop(strKey);
		return true;

	}
	REDIS_CATCH(__FUNCTION__, __LINE__);
	return false;
}

bool AFCRedisDriver::ListRange(const std::string & strKey, const int nStar, const int nEnd, std::vector<std::string>& xList)
{
	if (!enable())
	{
		return false;
	}

	try
	{

		m_pNoSqlClient->lrange(strKey, nStar, nEnd, xList);
		return true;
	}
	REDIS_CATCH(__FUNCTION__, __LINE__);
	return false;
}

bool AFCRedisDriver::ListLen(const std::string & strKey, int & nLength)
{
	if (!enable())
	{
		return false;
	}

	try
	{
		nLength = m_pNoSqlClient->llen(strKey);
		return true;
	}
	REDIS_CATCH(__FUNCTION__, __LINE__);

	return false;
}

bool AFCRedisDriver::ListIndex(const std::string & strKey, const int nIndex, std::string & strValue)
{
	if (!enable())
	{
		return false;
	}

	try
	{
		strValue = m_pNoSqlClient->lindex(strKey, nIndex);
		return true;
	}
	REDIS_CATCH(__FUNCTION__, __LINE__);


	return false;
}

bool AFCRedisDriver::ListRem(const std::string & strKey, const int nCount, const std::string & strValue)
{
	if (!enable())
	{
		return false;
	}

	try
	{

		m_pNoSqlClient->lrem(strKey, nCount, strValue);
		return true;
	}
	REDIS_CATCH(__FUNCTION__, __LINE__);

	return false;
}

bool AFCRedisDriver::ListSet(const std::string & strKey, const int nCount, const std::string & strValue)
{
	if (!enable())
	{
		return false;
	}

	try
	{

		m_pNoSqlClient->lset(strKey, nCount, strValue);
		return true;

	}
	REDIS_CATCH(__FUNCTION__, __LINE__);

	return false;
}

bool AFCRedisDriver::ListTrim(const std::string & strKey, const int nStar, const int nEnd)
{
	if (!enable())
	{
		return false;
	}

	try
	{
		m_pNoSqlClient->ltrim(strKey, nStar, nEnd);
		return true;
	}
	REDIS_CATCH(__FUNCTION__, __LINE__);
	return false;
}
