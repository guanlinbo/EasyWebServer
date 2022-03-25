//
// Created by 20882 on 2022/3/24.
//

#ifndef UNTITLED_EASYTCPSERVER_H
#define UNTITLED_EASYTCPSERVER_H

#include<sys/socket.h>
#include<arpa/inet.h>
#include <unistd.h>
#include <cstdio>
class EasyTcpServer
{
    int m_socket;
public:
    EasyTcpServer();
    //初始化套接字
    int InitSocket();
    //绑定服务器信息
    bool Bind(const char* ip, unsigned short port);
    //创建监听套接字
    void Listen() const;
    //连接客户端
    int Accept(struct sockaddr_in* _sin,socklen_t *__restrict _sinLen) const;
    //获取socket套接字
    int GetHandle() const;
    //关闭套接字
    void Close();
    //析构函数
    virtual ~EasyTcpServer();
    //判断套接字是否错误
    bool getSocketStatus() const;
};


#endif //UNTITLED_EASYTCPSERVER_H
