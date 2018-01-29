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
    virtual bool enable() = 0;

    //////////////////////////////////////////////////////////////////////////
    //Key
    virtual bool DEL(const std::string& key) = 0;
    virtual bool EXISTS(const std::string& key) = 0;
    virtual bool EXPIRE(const std::string& key, const uint32_t seconds) = 0;
    virtual bool EXPIREAT(const std::string& key, const int timestamp) = 0;

    //////////////////////////////////////////////////////////////////////////
    //String
    virtual bool SET(const std::string& key, const std::string& value) = 0;
    virtual bool GET(const std::string& key, OUT std::string& value) = 0;
    virtual bool SETNX(const std::string& key, const std::string& value) = 0;
    virtual bool SETEX(const std::string& key, const std::string& value, const uint32_t seconds) = 0;
    virtual bool HSET(const std::string& key, const std::string& field, const std::string& value) = 0;
    //////////////////////////////////////////////////////////////////////////
    //Hash
    virtual bool HGET(const std::string& key, const std::string& field, OUT std::string& value) = 0;
    virtual bool HMSET(const std::string& key, const std::vector<std::string>& fields, const std::vector<std::string>& values) = 0;
    virtual bool HMGET(const std::string& key, const std::vector<std::string>& fields, OUT std::vector<std::string>& values) = 0;
    virtual bool HEXISTS(const std::string& key, const std::string& field) = 0;
    virtual bool HDEL(const std::string& key, const std::string& field) = 0;
    virtual bool HLEN(const std::string& key, OUT int& length) = 0;
    virtual bool HKEYS(const std::string& key, OUT std::vector<std::string>& fields) = 0;
    virtual bool HVALS(const std::string& key, OUT std::vector<std::string>& values) = 0;
    virtual bool HGETALL(const std::string& key, OUT std::vector<std::pair<std::string, std::string>>& values) = 0;
    //////////////////////////////////////////////////////////////////////////
    //list
    virtual bool RPUSH(const std::string& key, const std::string& value) = 0;
    virtual bool RPOP(const std::string& key, OUT std::string& value) = 0;
    virtual bool LRANGE(const std::string& key, const int start, const int end, OUT std::vector<std::string>& elements) = 0;
    virtual bool LLEN(const std::string& key, OUT int& length) = 0;
    virtual bool LINDEX(const std::string& key, const int index, OUT std::string& value) = 0;
    virtual bool LREM(const std::string& key, const int count, const std::string& value) = 0;
    virtual bool LSET(const std::string& key, const int index, const std::string& value) = 0;
    virtual bool LTRIM(const std::string& key, const int start, const int end) = 0;
    //////////////////////////////////////////////////////////////////////////
    //SortedSet
    virtual bool ZADD(const std::string& key, const double score, const std::string& member) = 0;
    virtual bool ZCARD(const std::string& key, OUT int& count) = 0;
    virtual bool ZCOUNT(const std::string& key, const int min, const int max, OUT int& count) = 0;
    virtual bool ZINCRBY(const std::string& key, const double increment, const std::string& member) = 0;
    virtual bool ZREM(const std::string& key, const std::string& member) = 0;
    virtual bool ZREMRANGEBYRANK(const std::string& key, const int start, const int stop) = 0;
    virtual bool ZREMRANGEBYSCORE(const std::string& key, const int min, const int max) = 0;
    virtual bool ZREVRANGE(const std::string& key, const int start, const int stop, OUT std::vector<std::pair<std::string, double>>& member_scores) = 0;
    virtual bool ZREVRANK(const std::string& key, const std::string& strMember, int& nRank) = 0;
    virtual bool ZRANGEBYSCORE(const std::string& key, const int min, const int max, OUT std::vector<std::pair<std::string, double>>& member_scores) = 0;
    virtual bool ZSCORE(const std::string& key, const std::string& member, OUT double& score) = 0;
};