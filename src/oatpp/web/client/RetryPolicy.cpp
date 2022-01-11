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

#include "RetryPolicy.hpp"
#include <unordered_set>

#include <functional>
#include <ext/alloc_traits.h>
#include <ext/aligned_buffer.h>
#include "oatpp/core/base/Environment.hpp"
#include <chrono>

namespace oatpp { namespace web { namespace client {

SimpleRetryPolicy::SimpleRetryPolicy(v_int64 maxAttempts,
                                     const std::chrono::duration<v_int64, std::micro>& delay,
                                     const std::unordered_set<v_int32>& httpCodes)
  : m_maxAttempts(maxAttempts)
  , m_delay(delay.count())
  , m_httpCodes(httpCodes)
{}

bool SimpleRetryPolicy::canRetry(const Context& context) {
  return context.attempt <= m_maxAttempts || m_maxAttempts == -1;
}

bool SimpleRetryPolicy::retryOnResponse(v_int32 responseStatusCode, const Context& context) {
  (void) context;
  return m_httpCodes.find(responseStatusCode) != m_httpCodes.end();
}

v_int64 SimpleRetryPolicy::waitForMicroseconds(const Context& context) {
  (void) context;
  return m_delay;
}

}}}
