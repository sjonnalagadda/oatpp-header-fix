/***************************************************************************
*
* Project         _____    __   ____   _      _
*                (  _  )  /__\ (_  _)_| |_  _| |_
*                 )(_)(  /(__)\  )( (_   _)(_   _)
*                (_____)(__)(__)(__)  |_|    |_|
*
*
* Copyright 2018-present, Leonid Stryzhevskyi <lganzzzo@gmail.com>
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
***************************************************************************/

#ifndef oatpp_network_tcp_ConnectionConfigurer_hpp
#define oatpp_network_tcp_ConnectionConfigurer_hpp

#include "oatpp/core/IODefinitions.hpp"

namespace oatpp { namespace network { namespace tcp {

/**
 * Connection configurer
 */
class ConnectionConfigurer {
public:
  /**
   * Constructor.
   */
  virtual ~ConnectionConfigurer() = default;

  /**
   * Configure connection options.
   * @param connection
   */
  virtual void configure(oatpp::v_io_handle handle) = 0;
};

}}}

#endif
