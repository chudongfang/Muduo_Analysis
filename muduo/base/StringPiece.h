// Taken from PCRE pcre_stringpiece.h
//
// Copyright (c) 2005, Google Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Author: Sanjay Ghemawat
//
// A string like object that points into another piece of memory.
// Useful for providing an interface that allows clients to easily
// pass in either a "const char*" or a "string".
//
// Arghh!  I wish C++ literals were automatically of type "string".

#ifndef MUDUO_BASE_STRINGPIECE_H
#define MUDUO_BASE_STRINGPIECE_H

#include <string.h>
#include <iosfwd>    // for ostream forward-declaration

#include <muduo/base/Types.h>
#ifndef MUDUO_STD_STRING
#include <string>
#endif

namespace muduo {

// For passing C-style string argument to a function.
class StringArg // copyable
{
 public:
  //构造函数
  StringArg(const char* str)
    : str_(str)
  {     }

  //构造函数 string类型
  StringArg(const string& str)
    : str_(str.c_str())
  { }

#ifndef MUDUO_STD_STRING
  StringArg(const std::string& str)
    : str_(str.c_str())
  { }
#endif

  //返回对应指针
  const char* c_str() const { return str_; }

 private:
  //字符指针
  const char* str_;
};

class StringPiece {
 private:
  //存储指针
  const char*   ptr_;
  //字符串长度
  int           length_;

 public:
  // We provide non-explicit singleton constructors so users can pass
  // in a "const char*" or a "string" wherever a "StringPiece" is
  // expected.
  //构造函数，初始化
  StringPiece()
    : ptr_(NULL), length_(0) { }
  StringPiece(const char* str)
    : ptr_(str), length_(static_cast<int>(strlen(ptr_))) { }
  StringPiece(const unsigned char* str)
    : ptr_(reinterpret_cast<const char*>(str)),
      length_(static_cast<int>(strlen(ptr_))) { }
  StringPiece(const string& str)
    : ptr_(str.data()), length_(static_cast<int>(str.size())) { }
#ifndef MUDUO_STD_STRING
  StringPiece(const std::string& str)
    : ptr_(str.data()), length_(static_cast<int>(str.size())) { }
#endif
  StringPiece(const char* offset, int len)
    : ptr_(offset), length_(len) { }

  // data() may return a pointer to a buffer with embedded NULs, and the
  // returned buffer may or may not be null terminated.  Therefore it is
  // typically a mistake to pass data() to a routine that expects a NUL
  // terminated string.  Use "as_string().c_str()" if you really need to do
  // this.  Or better yet, change your routine so it does not rely on NUL
  // termination.
  //返回字符串指针 
  const char* data() const { return ptr_; }

  //返回字符串长度
  int size() const { return length_; }
  
  //判断是否为空
  bool empty() const { return length_ == 0; }
  
  //起始指针
  const char* begin() const { return ptr_; }
  
  //终止指针
  const char* end() const { return ptr_ + length_; }
  
  //清空
  void clear() { ptr_ = NULL; length_ = 0; }
  //重置
  void set(const char* buffer, int len) { ptr_ = buffer; length_ = len; }
  void set(const char* str) {
    ptr_ = str;
    length_ = static_cast<int>(strlen(str));
  }
  void set(const void* buffer, int len) {
    ptr_ = reinterpret_cast<const char*>(buffer);
    length_ = len;
  }

  //重载[]运算符
  char operator[](int i) const { return ptr_[i]; }
  //截掉前n个字符
  void remove_prefix(int n) {
    ptr_ += n;
    length_ -= n;
  }
  //截掉后n个字符
  void remove_suffix(int n) {
    length_ -= n;
  }
  
  //重载==运算符
  bool operator==(const StringPiece& x) const {
    return ((length_ == x.length_) &&
            (memcmp(ptr_, x.ptr_, length_) == 0));
  }
  //重载不等于运算符
  bool operator!=(const StringPiece& x) const {
    return !(*this == x);
  }

#define STRINGPIECE_BINARY_PREDICATE(cmp,auxcmp)                             \
  bool operator cmp (const StringPiece& x) const {                           \
    int r = memcmp(ptr_, x.ptr_, length_ < x.length_ ? length_ : x.length_); \
    return ((r auxcmp 0) || ((r == 0) && (length_ cmp x.length_)));          \
  }
  STRINGPIECE_BINARY_PREDICATE(<,  <);
  STRINGPIECE_BINARY_PREDICATE(<=, <);
  STRINGPIECE_BINARY_PREDICATE(>=, >);
  STRINGPIECE_BINARY_PREDICATE(>,  >);
#undef STRINGPIECE_BINARY_PREDICATE
  //比较两个对象是否相等，利用memcmp进行比较
  int compare(const StringPiece& x) const {
    int r = memcmp(ptr_, x.ptr_, length_ < x.length_ ? length_ : x.length_);
    if (r == 0) {
      if (length_ < x.length_) r = -1;
      else if (length_ > x.length_) r = +1;
    }
    return r;
  }

  //以 string 类型返回
  string as_string() const {
    return string(data(), size());
  }

  void CopyToString(string* target) const {
    target->assign(ptr_, length_);
  }

#ifndef MUDUO_STD_STRING
  void CopyToStdString(std::string* target) const {
    //将string 内容清空，并将ptr_字符串赋值给string
    target->assign(ptr_, length_);
  }
#endif
  //将StringPiece与当前字符串比较是否相同
  // Does "this" start with "x"
  bool starts_with(const StringPiece& x) const {
    return ((length_ >= x.length_) && (memcmp(ptr_, x.ptr_, x.length_) == 0));
  }
};

}   // namespace muduo

// ------------------------------------------------------------------
// Functions used to create STL containers that use StringPiece
//  Remember that a StringPiece's lifetime had better be less than
//  that of the underlying string or char*.  If it is not, then you
//  cannot safely store a StringPiece into an STL container
// ------------------------------------------------------------------

#ifdef HAVE_TYPE_TRAITS
// 经过特化的StringPiece 
// This makes vector<StringPiece> really fast for some STL implementations
template<> struct __type_traits<muduo::StringPiece> {
  typedef __true_type    has_trivial_default_constructor;//有构造函数
  typedef __true_type    has_trivial_copy_constructor;   //有复制构造函数
  typedef __true_type    has_trivial_assignment_operator;//有赋值函数
  typedef __true_type    has_trivial_destructor;         //有析构函数
  typedef __true_type    is_POD_type;                    //是C++的内建类型或传统的C结构体类型
};
#endif

// allow StringPiece to be logged
// 重载运算符，以便写日志
std::ostream& operator<<(std::ostream& o, const muduo::StringPiece& piece);

#endif  // MUDUO_BASE_STRINGPIECE_H
