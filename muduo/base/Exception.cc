// Use of this source code is governed by a BSD-style license // that can be found in the License file.
//
// Author: Shuo Chen (chenshuo at chenshuo dot com)

#include <muduo/base/Exception.h>

//#include <cxxabi.h>
#include <execinfo.h>
#include <stdlib.h>

using namespace muduo;
//构造函数
Exception::Exception(const char* msg)
  : message_(msg)
{
  fillStackTrace();
}
//构造函数
Exception::Exception(const string& msg)
  : message_(msg)
{
  fillStackTrace();
}
//析构函数
Exception::~Exception() throw ()
{
}
//返回出错信息
const char* Exception::what() const throw()
{
  return message_.c_str();
}
//返回堆栈信息
const char* Exception::stackTrace() const throw()
{
  return stack_.c_str();
}

void Exception::fillStackTrace()
{
  const int len = 200;
  void* buffer[len];
  //该函数用与获取当前线程的调用堆栈
  int nptrs = ::backtrace(buffer, len);
  //backtrace_symbols将从backtrace函数获取的信息转化为一个字符串数组
  char** strings = ::backtrace_symbols(buffer, nptrs);
  if (strings)
  {
    for (int i = 0; i < nptrs; ++i)
    {
      // TODO demangle funcion name with abi::__cxa_demangle
      stack_.append(strings[i]);
      stack_.push_back('\n');
    }
    free(strings);
  }
}

