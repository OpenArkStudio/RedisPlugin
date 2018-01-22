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

#include "SDK/Interface/AFIModule.h"
#include "Interface/AFIRedisDriver.h"

class AFIRedisModule : public AFIModule
{
public:
    virtual bool ConnectRedis(const std::string& ip, const uint16_t port, const std::string& password = NULL_STR, const uint8_t db_index = 1) = 0;
    virtual ARK_SHARE_PTR<AFIRedisDriver> GetDriver() = 0;
};