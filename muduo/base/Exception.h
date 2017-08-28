// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Shuo Chen (chenshuo at chenshuo dot com)

#ifndef MUDUO_BASE_EXCEPTION_H
#define MUDUO_BASE_EXCEPTION_H

#include <muduo/base/Types.h>
#include <exception>

namespace muduo
{

//重载boost库中的exception基类
class Exception : public std::exception
{
 public:
  explicit Exception(const char* what);//构造函数
  explicit Exception(const string& what);//重载构造函数
  virtual ~Exception() throw();//析构函数
  virtual const char* what() const throw();//返回出错信息
  const char* stackTrace() const throw();//返回堆栈信息

 private:
  void fillStackTrace();//存储堆栈信息

  string message_;//用来存储出错信息
  string stack_;//用来存储堆栈信息
};

}

#endif  // MUDUO_BASE_EXCEPTION_H
