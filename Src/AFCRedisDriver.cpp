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
    if (!enable())
    {
        return false;
    }

    aredis::redis_command cmd;
    cmd.cmd("SETNX", key, value);
    m_pRedisClient->command(cmd);
    aredis::resp_result result;
    return m_pRedisClient->reply(result);
}

bool AFCRedisDriver::SETEX(const std::string& key, const std::string& value, const uint32_t seconds)
{
    if (!enable())
    {
        return false;
    }

    aredis::redis_command cmd;
    cmd.cmd("SETEX", key, seconds);
    m_pRedisClient->command(cmd);
    aredis::resp_result result;
    return m_pRedisClient->reply(result);
}

bool AFCRedisDriver::HSET(const std::string& key, const std::string& field, const std::string& value)
{
    if (!enable())
    {
        return false;
    }

    aredis::redis_command cmd;
    cmd.cmd("HSET", key, field, value);
    m_pRedisClient->command(cmd);
    aredis::resp_result result;
    return m_pRedisClient->reply(result);
}

bool AFCRedisDriver::HGET(const std::string& key, const std::string& field, OUT std::string& value)
{
    if (!enable())
    {
        return false;
    }

    aredis::redis_command cmd;
    cmd.cmd("HGET", key, field);
    m_pRedisClient->command(cmd);
    aredis::resp_result result;
    if (m_pRedisClient->reply(result))
    {
        value = result.dump();
        return true;
    }

    return false;
}

bool AFCRedisDriver::HMSET(const std::string& key, const std::vector<std::string>& fields, const std::vector<std::string>& values)
{
    if (!enable())
    {
        return false;
    }

    if (fields.size() != values.size())
    {
        return false;
    }

    aredis::redis_command cmd;
    cmd.cmd("HMSET", key);
    for (size_t i = 0; i < fields.size(); ++i)
    {
        cmd.arg(fields[i]);
        cmd.arg(values[i]);
    }
    m_pRedisClient->command(cmd);
    aredis::resp_result result;
    return m_pRedisClient->reply(result);
}

bool AFCRedisDriver::HMGET(const std::string& key, const std::vector<std::string>& fields, OUT std::vector<std::string>& values)
{
    if (!enable())
    {
        return false;
    }

    if (fields.empty())
    {
        return false;
    }

    aredis::redis_command cmd;
    cmd.cmd("HMGET", key);
    for (size_t i = 0; i < fields.size(); ++i)
    {
        cmd.arg(fields[i]);
    }

    m_pRedisClient->command(cmd);

    aredis::resp_result result;
    if (m_pRedisClient->reply(result))
    {
        for (size_t i = 0; i < fields.size(); ++i)
        {
            aredis::resp_value resp = result.value(i);
            values.emplace_back(resp.values.svalue);
        }
        
        return true;
    }

    return false;
}

bool AFCRedisDriver::HEXISTS(const std::string& key, const std::string& field)
{
    if (!enable())
    {
        return false;
    }

    aredis::redis_command cmd;
    cmd.cmd("HEXISTS", key, field);
    m_pRedisClient->command(cmd);
    aredis::resp_result result;
    return m_pRedisClient->reply(result);
}

bool AFCRedisDriver::HDEL(const std::string& key, const std::string& field)
{
    if (!enable())
    {
        return false;
    }

    aredis::redis_command cmd;
    cmd.cmd("HDEL", key, field);
    m_pRedisClient->command(cmd);
    aredis::resp_result result;
    return m_pRedisClient->reply(result);
}

bool AFCRedisDriver::HLEN(const std::string& key, OUT int& length)
{
    if (!enable())
    {
        return false;
    }

    aredis::redis_command cmd;
    cmd.cmd("HLEN", key);
    m_pRedisClient->command(cmd);
    aredis::resp_result result;
    if (m_pRedisClient->reply(result))
    {
        length = ARK_LEXICAL_CAST<int>(result.dump());
        return true;
    }
    
    return false;
}

bool AFCRedisDriver::HKEYS(const std::string& key, OUT std::vector<std::string>& fields)
{
    if (!enable())
    {
        return false;
    }

    aredis::redis_command cmd;
    cmd.cmd("HKEYS", key);
    m_pRedisClient->command(cmd);
    aredis::resp_result result;
    if (m_pRedisClient->reply(result))
    {
        for (size_t i = 0; i < result.dvals.size(); ++i)
        {
            aredis::resp_value resp = result.value(i);
            fields.push_back(resp.values.svalue);
        }

        return true;
    }

    return false;
}

bool AFCRedisDriver::HVALS(const std::string& key, OUT std::vector<std::string>& values)
{
    if (!enable())
    {
        return false;
    }

    aredis::redis_command cmd;
    cmd.cmd("HVALS", key);
    m_pRedisClient->command(cmd);
    aredis::resp_result result;
    if (m_pRedisClient->reply(result))
    {
        for (size_t i = 0; i < result.dvals.size(); ++i)
        {
            aredis::resp_value resp = result.value(i);
            values.push_back(resp.values.svalue);
        }

        return true;
    }

    return false;
}

bool AFCRedisDriver::HGETALL(const std::string& key, OUT std::vector<std::pair<std::string, std::string>>& values)
{
    if (!enable())
    {
        return false;
    }

    aredis::redis_command cmd;
    cmd.cmd("HGETALL", key);
    m_pRedisClient->command(cmd);
    aredis::resp_result result;
    if (m_pRedisClient->reply(result))
    {
        for (size_t i = 0; i < result.dvals.size(); i += 2)
        {
            aredis::resp_value resp_field = result.value(i);
            aredis::resp_value resp_value = result.value(i + 1);
            std::pair < std::string, std::string> pair_data(resp_field.values.svalue, resp_value.values.svalue);
            values.push_back(pair_data);
        }

        return true;
    }

    return false;
}

bool AFCRedisDriver::RPUSH(const std::string& key, const std::string& value)
{
    if (!enable())
    {
        return false;
    }

    aredis::redis_command cmd;
    cmd.cmd("RPUSH", key, value);
    m_pRedisClient->command(cmd);
    aredis::resp_result result;
    return m_pRedisClient->reply(result);
}

bool AFCRedisDriver::RPOP(const std::string& key, OUT std::string& value)
{
    if (!enable())
    {
        return false;
    }

    aredis::redis_command cmd;
    cmd.cmd("RPOP", key);
    m_pRedisClient->command(cmd);
    aredis::resp_result result;
    if (m_pRedisClient->reply(result))
    {
        value = result.dump();
        return true;
    }

    return false;
}

bool AFCRedisDriver::LRANGE(const std::string& key, const int start, const int end, OUT std::vector<std::string>& elements)
{
    if (!enable())
    {
        return false;
    }

    aredis::redis_command cmd;
    cmd.cmd("LRANGE", key, start, end);
    m_pRedisClient->command(cmd);
    aredis::resp_result result;
    if (m_pRedisClient->reply(result))
    {
        for (size_t i = 0; i < result.dvals.size(); ++i)
        {
            elements.emplace_back(result.dvals[i].values.svalue);
        }

        return true;
    }

    return false;
}

bool AFCRedisDriver::LLEN(const std::string& key, OUT int& length)
{
    if (!enable())
    {
        return false;
    }

    aredis::redis_command cmd;
    cmd.cmd("LLEN", key);
    m_pRedisClient->command(cmd);
    aredis::resp_result result;
    if (m_pRedisClient->reply(result))
    {
        length = ARK_LEXICAL_CAST<int>(result.dump());
        return true;
    }

    return false;
}

bool AFCRedisDriver::LINDEX(const std::string& key, const int index, OUT std::string& value)
{
    if (!enable())
    {
        return false;
    }

    aredis::redis_command cmd;
    cmd.cmd("LINDEX", key, index);
    m_pRedisClient->command(cmd);
    aredis::resp_result result;
    if (m_pRedisClient->reply(result))
    {
        value = result.dump();
        return true;
    }

    return false;
}

bool AFCRedisDriver::LREM(const std::string& key, const int count, const std::string& value)
{
    if (!enable())
    {
        return false;
    }

    aredis::redis_command cmd;
    cmd.cmd("LREM", key, count, value);
    m_pRedisClient->command(cmd);
    aredis::resp_result result;
    return m_pRedisClient->reply(result);
}

bool AFCRedisDriver::LSET(const std::string& key, const int index, const std::string& value)
{
    if (!enable())
    {
        return false;
    }

    aredis::redis_command cmd;
    cmd.cmd("LSET", key, index, value);
    m_pRedisClient->command(cmd);
    aredis::resp_result result;
    return m_pRedisClient->reply(result);
}

bool AFCRedisDriver::LTRIM(const std::string& key, const int start, const int end)
{
    if (!enable())
    {
        return false;
    }

    aredis::redis_command cmd;
    cmd.cmd("LTRIM", key, start, end);
    m_pRedisClient->command(cmd);
    aredis::resp_result result;
    return m_pRedisClient->reply(result);
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
