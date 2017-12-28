#include <muduo/net/EventLoop.h>
#include <muduo/net/EventLoopThread.h>
#include<muduo/net/EventLoop.cc>
#include<muduo/net/EventLoopThread.cc>
#include <stdio.h>

using namespace muduo;
using namespace muduo::net;

void runInThread()
{
    printf("runInThread(): pid = %d, tid = %d\n",
           getpid(), CurrentThread::tid());
}

int main()
{
    printf("main(): pid = %d, tid = %d\n",
           getpid(), CurrentThread::tid());

    EventLoopThread loopThread;
    EventLoop *loop = loopThread.startLoop();
    // 异步调用runInThread，即将runInThread添加到loop对象所在IO线程，让该IO线程执行
    loop->runInLoop(runInThread);
    sleep(1);
    // runAfter内部也调用了runInLoop，所以这里也是异步调用，让该IO线程添加一个2s定时器
    loop->runAfter(2, runInThread);
    sleep(3);
    //~EventLoopThread()会调用loop_->quit();

    printf("exit main().\n");
}
