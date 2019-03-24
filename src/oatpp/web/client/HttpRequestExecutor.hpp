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

#ifndef oatpp_web_client_HttpRequestExecutor_hpp
#define oatpp_web_client_HttpRequestExecutor_hpp

#include "./RequestExecutor.hpp"

#include "oatpp/web/protocol/http/incoming/SimpleBodyDecoder.hpp"
#include "oatpp/network/ConnectionProvider.hpp"

namespace oatpp { namespace web { namespace client {

/**
 * Default implementation of &id:oatpp::web::client::RequestExecutor; for making http request.
 */
class HttpRequestExecutor : public oatpp::base::Countable, public RequestExecutor {
private:
  typedef oatpp::web::protocol::http::Header Header;
protected:
  std::shared_ptr<oatpp::network::ClientConnectionProvider> m_connectionProvider;
  std::shared_ptr<const oatpp::web::protocol::http::incoming::BodyDecoder> m_bodyDecoder;
public:
  /**
   * Connection handle for &l:HttpRequestExecutor; <br>
   * For more details see &id:oatpp::web::client::RequestExecutor::ConnectionHandle;.
   */
  class HttpConnectionHandle : public ConnectionHandle {
  public:

    /**
     * Constructor.
     * @param stream - &id:oatpp::network::ConnectionProvider::IOStream;.
     */
    HttpConnectionHandle(const std::shared_ptr<oatpp::network::ConnectionProvider::IOStream>& stream)
      : connection(stream)
    {}

    /**
     * Connection.
     */
    std::shared_ptr<oatpp::network::ConnectionProvider::IOStream> connection;
  };
public:

  /**
   * Constructor.
   * @param connectionProvider - &id:oatpp::network::ClientConnectionProvider;.
   * @param bodyDecoder - &id:oatpp::web::protocol::http::incoming::BodyDecoder;.
   */
  HttpRequestExecutor(const std::shared_ptr<oatpp::network::ClientConnectionProvider>& connectionProvider,
                      const std::shared_ptr<const oatpp::web::protocol::http::incoming::BodyDecoder>& bodyDecoder =
                      std::make_shared<oatpp::web::protocol::http::incoming::SimpleBodyDecoder>());
public:

  /**
   * Create shared HttpRequestExecutor.
   * @param connectionProvider - &id:oatpp::network::ClientConnectionProvider;.
   * @param bodyDecoder - &id:oatpp::web::protocol::http::incoming::BodyDecoder;.
   * @return - `std::shared_ptr` to `HttpRequestExecutor`.
   */
  static std::shared_ptr<HttpRequestExecutor>
  createShared(const std::shared_ptr<oatpp::network::ClientConnectionProvider>& connectionProvider,
               const std::shared_ptr<const oatpp::web::protocol::http::incoming::BodyDecoder>& bodyDecoder =
               std::make_shared<oatpp::web::protocol::http::incoming::SimpleBodyDecoder>());

  /**
   * Get &id:oatpp::web::client::RequestExecutor::ConnectionHandle;
   * @return - ConnectionHandle which is &l:HttpRequestExecutor::HttpConnectionHandle;.
   */
  std::shared_ptr<ConnectionHandle> getConnection() override;

  /**
   * Same as &l:HttpRequestExecutor::getConnection (); but async.
   * @param parentCoroutine - caller coroutine as &id:oatpp::async::AbstractCoroutine;*.
   * @param callback - function pointer to asynchronous callback.
   * @return - &id:oatpp::async::Action;
   */
  Action getConnectionAsync(oatpp::async::AbstractCoroutine* parentCoroutine, AsyncConnectionCallback callback) override;

  /**
   * Execute http request.
   * @param method - method ex: ["GET", "POST", "PUT", etc.].
   * @param path - path to resource.
   * @param headers - headers map &id:oatpp::web::client::RequestExecutor::Headers;.
   * @param body - `std::shared_ptr` to &id:oatpp::web::client::RequestExecutor::Body; object.
   * @param connectionHandle - ConnectionHandle obtain in call to &l:HttpRequestExecutor::getConnection ();.
   * @return - &id:oatpp::web::protocol::http::incoming::Response;.
   * @throws - &id:oatpp::web::client::RequestExecutor::RequestExecutionError;
   */
  std::shared_ptr<Response> execute(const String& method,
                                    const String& path,
                                    const Headers& headers,
                                    const std::shared_ptr<Body>& body,
                                    const std::shared_ptr<ConnectionHandle>& connectionHandle = nullptr) override;

  /**
   * Same as &l:HttpRequestExecutor::execute (); but Async.
   * @param parentCoroutine - caller coroutine as &id:oatpp::async::AbstractCoroutine;*.
   * @param callback - function pointer to asynchronous callback.
   * @param method - method ex: ["GET", "POST", "PUT", etc.].
   * @param path - path to resource.
   * @param headers - headers map &id:oatpp::web::client::RequestExecutor::Headers;.
   * @param body - `std::shared_ptr` to &id:oatpp::web::client::RequestExecutor::Body; object.
   * @param connectionHandle - ConnectionHandle obtain in call to &l:HttpRequestExecutor::getConnection ();.
   * @return - &id:oatpp::async::Action;.
   */
  Action executeAsync(oatpp::async::AbstractCoroutine* parentCoroutine,
                      AsyncCallback callback,
                      const String& method,
                      const String& path,
                      const Headers& headers,
                      const std::shared_ptr<Body>& body,
                      const std::shared_ptr<ConnectionHandle>& connectionHandle = nullptr) override;
  
};
  
}}}

#endif /* oatpp_web_client_HttpRequestExecutor_hpp */
