// Copyright 2010, Shuo Chen.  All rights reserved.
// http://code.google.com/p/muduo/
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.

// Author: Shuo Chen (chenshuo at chenshuo dot com)

#include <muduo/net/EventLoopThread.h>

#include <muduo/net/EventLoop.h>

#include <boost/bind.hpp>

using namespace muduo;
using namespace muduo::net;

//构造函数
EventLoopThread::EventLoopThread(const ThreadInitCallback& cb,
                                 const string& name)
  : loop_(NULL),
    exiting_(false),
    thread_(boost::bind(&EventLoopThread::threadFunc, this), name),//初始化线程对象
    mutex_(),
    cond_(mutex_),//初始化条件变量
    callback_(cb) //初始化回调函数
{
}


//析构函数
EventLoopThread::~EventLoopThread()
{
  exiting_ = true;
  if (loop_ != NULL) // not 100% race-free, eg. threadFunc could be running callback_.
  {
    // still a tiny chance to call destructed object, if threadFunc exits just now.
    // but when EventLoopThread destructs, usually programming is exiting anyway.
    loop_->quit();//退出loop
    thread_.join();//阻塞子线程
  }
}


//开始loop
EventLoop* EventLoopThread::startLoop()
{
  assert(!thread_.started());
  thread_.start();
  //因为要涉及到两个线程访问同一个变量，所以用条件变量进行保护
  //等待子线程创建完loop后再返回
  {
    MutexLockGuard lock(mutex_);
    while (loop_ == NULL)
    {
      cond_.wait();
    }
  }

  return loop_;
}

//线程函数
void EventLoopThread::threadFunc()
{
  EventLoop loop;
  //如果存在回调函数，调用回调函数对loop进行修改
  if (callback_)
  {
    callback_(&loop);
  }
  
  //当线程成功创建了loop就唤醒父线程返回loop
  {
    MutexLockGuard lock(mutex_);
    loop_ = &loop;
    cond_.notify();
  }
  //开始loop
  loop.loop();
  //assert(exiting_);
  loop_ = NULL;
}

