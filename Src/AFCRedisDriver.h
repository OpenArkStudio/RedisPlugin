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

    //////////////////////////////////////////////////////////////////////////
    //Key
	virtual bool DEL(const std::string& key);
	virtual bool EXISTS(const std::string& key);
	virtual bool EXPIRE(const std::string& key, const uint32_t seconds);
	virtual bool EXPIREAT(const std::string& key, const int timestamp);

	//////////////////////////////////////////////////////////////////////////
    //String
	virtual bool SET(const std::string& key, const std::string& value);
	virtual bool GET(const std::string& key, OUT std::string& value);
	virtual bool SETNX(const std::string& key, const std::string& value);
	virtual bool SETEX(const std::string& key, const std::string& value, const uint32_t seconds);
    virtual bool HSET(const std::string& key, const std::string& field, const std::string& value);
    //////////////////////////////////////////////////////////////////////////
    //Hash
    virtual bool HGET(const std::string& key, const std::string& field, OUT std::string& value);
    virtual bool HMSET(const std::string& key, const std::vector<std::string>& fields, const std::vector<std::string>& values);
    virtual bool HMGET(const std::string& key, const std::vector<std::string>& fields, OUT std::vector<std::string>& values);
    virtual bool HEXISTS(const std::string& key, const std::string& field);
    virtual bool HDEL(const std::string& key, const std::string& field);
    virtual bool HLEN(const std::string& key, OUT int& length);
    virtual bool HKEYS(const std::string& key, OUT std::vector<std::string>& fields);
    virtual bool HVALS(const std::string& key, OUT std::vector<std::string>& values);
    virtual bool HGETALL(const std::string& key, OUT std::vector<std::pair<std::string, std::string>>& values);
    //////////////////////////////////////////////////////////////////////////
    //list
    virtual bool RPUSH(const std::string& key, const std::string& value);
    virtual bool RPOP(const std::string& key, std::string& value);
    virtual bool LRANGE(const std::string& key, const int start, const int end, OUT std::vector<std::string>& elements);
    virtual bool LLEN(const std::string& key, OUT int& length);
    virtual bool LINDEX(const std::string& key, const int index, OUT std::string& value);
    virtual bool LREM(const std::string& key, const int count, const std::string& value);
    virtual bool LSET(const std::string& key, const int count, const std::string& value);
    virtual bool LTRIM(const std::string& key, const int start, const int end);
    //////////////////////////////////////////////////////////////////////////
    //SortedSet
	virtual bool ZADD(const std::string& key, const double score, const std::string& member);
    virtual bool ZCARD(const std::string& key, OUT int& count);
    virtual bool ZCOUNT(const std::string& key, const int min, const int max, OUT int& count);
	virtual bool ZINCRBY(const std::string& key, const double increment, const std::string& member);
    virtual bool ZREM(const std::string& key, const std::string& member);
    virtual bool ZREMRANGEBYRANK(const std::string& key, const int start, const int stop);
    virtual bool ZREMRANGEBYSCORE(const std::string& key, const int min, const int max);
    virtual bool ZREVRANGE(const std::string& key, const int start, const int stop, OUT std::vector<std::pair<std::string, double>>& member_scores);
    virtual bool ZREVRANK(const std::string& key, const std::string& strMember, int& nRank);
    virtual bool ZRANGEBYSCORE(const std::string& key, const int min, const int max, OUT std::vector<std::pair<std::string, double>>& member_scores);
	virtual bool ZSCORE(const std::string& key, const std::string& member, OUT double& score);

private:
	bool mbEnable;
    ARK_SHARE_PTR<aredis::redis_conn> m_pRedisClient;
};