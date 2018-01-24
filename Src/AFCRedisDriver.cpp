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

bool AFCRedisDriver::DEL(const std::string& key)
{
	if (!enable())
	{
		return false;
	}

    aredis::redis_command cmd;
    cmd.cmd("DEL", key);
    m_pRedisClient->command(cmd);
    aredis::resp_result result;
    return m_pRedisClient->reply(result);
}

bool AFCRedisDriver::EXISTS(const std::string& key)
{
	if (!enable())
	{
		return false;
	}

    aredis::redis_command cmd;
    cmd.cmd("EXISTS", key);
    m_pRedisClient->command(cmd);
    aredis::resp_result result;
    return m_pRedisClient->reply(result);
}

bool AFCRedisDriver::EXPIRE(const std::string& key, uint32_t seconds)
{
	if (!enable())
	{
		return false;
	}

    aredis::redis_command cmd;
    cmd.cmd("EXPIRE", key, seconds);
    m_pRedisClient->command(cmd);
    aredis::resp_result result;
    return m_pRedisClient->reply(result);
}

bool AFCRedisDriver::EXPIREAT(const std::string& key, int timestamp)
{
    if (!enable())
    {
        return false;
    }

    aredis::redis_command cmd;
    cmd.cmd("EXPIREAT", key, timestamp);
    m_pRedisClient->command(cmd);
    aredis::resp_result result;
    return m_pRedisClient->reply(result);
}

bool AFCRedisDriver::SET(const std::string& key, const std::string& value)
{
    if (!enable())
    {
    	return false;
    }
    
    aredis::redis_command cmd;
    cmd.cmd("SET", key, value);
    m_pRedisClient->command(cmd);
    aredis::resp_result result;
    return m_pRedisClient->reply(result);
}

bool AFCRedisDriver::GET(const std::string& key, OUT std::string& value)
{
    if (!enable())
    {
    	return false;
    }
    
    aredis::redis_command cmd;
    cmd.cmd("GET", key);
    m_pRedisClient->command(cmd);
    aredis::resp_result result;
    if (m_pRedisClient->reply(result))
    {
        value = result.dump();
        return true;
    }
    
    return false;
}

bool AFCRedisDriver::SETNX(const std::string& key, const std::string& value)
{
    return false;
}

bool AFCRedisDriver::SETEX(const std::string& key, const std::string& value, const uint32_t seconds)
{
    return false;
}

bool AFCRedisDriver::HSET(const std::string& key, const std::string& field, const std::string& value)
{
    return false;
}

bool AFCRedisDriver::HGET(const std::string& key, const std::string& field, OUT std::string& value)
{
    return false;
}

bool AFCRedisDriver::HMSET(const std::string& key, const std::vector<std::string>& fields, const std::vector<std::string>& values)
{
    return false;
}

bool AFCRedisDriver::HMGET(const std::string& key, const std::vector<std::string>& fields, OUT std::vector<std::string>& values)
{
    return false;
}

bool AFCRedisDriver::HEXISTS(const std::string& key, const std::string& fields)
{
    return false;
}

bool AFCRedisDriver::HDEL(const std::string& key, const std::string& fields)
{
    return false;
}

bool AFCRedisDriver::HLEN(const std::string& key, OUT int& length)
{
    return false;
}

bool AFCRedisDriver::HKEYS(const std::string& key, OUT std::vector<std::string>& fields)
{
    return false;
}

bool AFCRedisDriver::HVALS(const std::string& key, OUT std::vector<std::string>& values)
{
    return false;
}

bool AFCRedisDriver::HGETALL(const std::string& key, OUT std::vector<std::pair<std::string, std::string>>& values)
{
    return false;
}

bool AFCRedisDriver::RPUSH(const std::string& key, const std::string& value)
{
    return false;
}

bool AFCRedisDriver::RPOP(const std::string& key, std::string& value)
{
    return false;
}

bool AFCRedisDriver::LRANGE(const std::string& key, const int start, const int end, OUT std::vector<std::string>& elements)
{
    return false;
}

bool AFCRedisDriver::LLEN(const std::string& key, OUT int& length)
{
    return false;
}

bool AFCRedisDriver::LINDEX(const std::string& key, const int index, OUT std::string& value)
{
    return false;
}

bool AFCRedisDriver::LREM(const std::string& key, const int count, const std::string& value)
{
    return false;
}

bool AFCRedisDriver::LSET(const std::string& key, const int count, const std::string& value)
{
    return false;
}

bool AFCRedisDriver::LTRIM(const std::string& key, const int start, const int end)
{
    return false;
}

bool AFCRedisDriver::ZADD(const std::string& key, const double score, const std::string& member)
{
    return false;
}

bool AFCRedisDriver::ZCARD(const std::string& key, OUT int& count)
{
    return false;
}

bool AFCRedisDriver::ZCOUNT(const std::string& key, const int min, const int max, OUT int& count)
{
    return false;
}

bool AFCRedisDriver::ZINCRBY(const std::string& key, const double increment, const std::string& member)
{
    return false;
}

bool AFCRedisDriver::ZREM(const std::string& key, const std::string& member)
{
    return false;
}

bool AFCRedisDriver::ZREMRANGEBYRANK(const std::string& key, const int start, const int stop)
{
    return false;
}

bool AFCRedisDriver::ZREMRANGEBYSCORE(const std::string& key, const int min, const int max)
{
    return false;
}

bool AFCRedisDriver::ZREVRANGE(const std::string& key, const int start, const int stop, OUT std::vector<std::pair<std::string, double>>& member_scores)
{
    return false;
}

bool AFCRedisDriver::ZREVRANK(const std::string& key, const std::string& strMember, int& nRank)
{
    return false;
}

bool AFCRedisDriver::ZRANGEBYSCORE(const std::string& key, const int min, const int max, OUT std::vector<std::pair<std::string, double>>& member_scores)
{
    return false;
}

bool AFCRedisDriver::ZSCORE(const std::string& key, const std::string& member, OUT double& score)
{
    return false;
}
