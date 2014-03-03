/*
 *  This file is part of clearskies_core file synchronization program
 *  Copyright (C) 2014 Pedro Larroy

 *  clearskies_core is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.

 *  clearskies_core is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.

 *  You should have received a copy of the GNU Lesser General Public License
 *  along with clearskies_core.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once
#include "config.hpp"
#include "share.hpp"
#include "protocolstate.hpp"
#include "clearskiesprotocol.hpp"
#include <string>
#include <map>

namespace cs
{

namespace server
{


/**
 * Base class for connections to peers
 */
class Connection
{
public:
    Connection(
        const std::map<std::string, share::Share>& shares
    ):
        m_cs_protocol(shares)
    {}

    virtual ~Connection() = default;

    Connection(const Connection&) = delete;
    Connection& operator=(const Connection&) = delete;
    Connection(Connection&&) = default;
    Connection& operator=(Connection&&) = default;

    cs::protocol::ClearSkiesProtocol m_cs_protocol;
};



/**
 * Base class that knows about some shares and where to they map in the filesystem
 */
class Server 
{
public:
    Server(): 
          m_software{}
        , m_protocol{1}
        , m_features{}
        , m_shares{}
        , m_connections{}
    {}

    Server(const Server&) = delete;
    Server& operator=(const Server&) = delete;
    Server(Server&&) = default;
    Server& operator=(Server&&) = default;

    void attach_share(const std::string& share_path, const std::string& dbpath = std::string());

public:
    std::string m_software;
    i32 m_protocol;
    std::vector<std::string> m_features;


protected:
    /// share id to @sa share::Share, the share knows the path
    std::map<std::string, share::Share> m_shares;
    /// connection identifier to Connection
    std::map<std::string, std::unique_ptr<Connection>> m_connections;

};



} // end ns
} // end ns

