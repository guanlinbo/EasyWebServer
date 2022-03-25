/* ************************************************************************
 *       Filename:  EasyTcpServer.cpp
 *    Description:
 *        Version:  1.0
 *        Created:  2022年03月24日 20时18分53秒
 *       Revision:  none
 *         Author:  guanlinbo
 * ************************************************************************/
#include <cstring>
#include <cerrno>
#include "EasyTcpServer.h"
EasyTcpServer::EasyTcpServer() : m_socket(-1) {}

int EasyTcpServer::GetHandle() const {
    return this->m_socket;
}

void EasyTcpServer::Close()  {
    if(getSocketStatus())
    {
        close(this->m_socket);
        printf("关闭套接字成功！\n");
        this->m_socket = -1;
    }
}

EasyTcpServer::~EasyTcpServer() {
    this->Close();
}

int EasyTcpServer::InitSocket() {
    if(getSocketStatus())
    {
        printf("<socket=%un>关闭旧连接!\n", this->m_socket);
        this->Close();
    }
    //配置监听socket
    this->m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (-1 == this->m_socket)
    {
        printf("错误，建立Socket失败!\n");
    }
    else
    {
        printf("创建Socket成功!\n");
    }
    return this->m_socket;
}

bool EasyTcpServer::Bind(const char *ip, unsigned short port) {
    //判断参数是否正确
    if(port>=65535)
    {
        printf("参数错误!\n");
        return false;
    }
    //如果没有初始化直接绑定，那么就初始化一下socket
    if(!getSocketStatus())
    {
        this->InitSocket();
    }
    struct sockaddr_in _sin = {};
    _sin.sin_port = htons(port);
    if(!ip || (0 == strcmp("0.0.0.0",ip)))
    {
        _sin.sin_addr.s_addr = INADDR_ANY;
    }
    else
    {
        _sin.sin_addr.s_addr = inet_addr(ip);
    }
    _sin.sin_family = AF_INET;
    //设置端口复用
    int opt = 1;
    setsockopt(this->m_socket,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
    if(-1 == bind(this->m_socket,(sockaddr*)&_sin,sizeof(_sin)))
    {
        printf("错误之前socket的信息: socket = %d port = %u\n",this->m_socket,port);
        perror("bind error");
        return false;
    }
    return true;
}

void EasyTcpServer::Listen() const {
    if(!getSocketStatus())
    {
        printf("socket error\n");
        return;
    }
    int ret = listen(this->m_socket,128);
    if(ret < 0)
    {
        printf("监听网络套接字失败!\n");
    }
    else
    {
        printf("监听网络套接字成功!\n");
    }
}

bool EasyTcpServer::getSocketStatus() const {
    if(-1 == this->m_socket)
    {
        return false;
    }
    return true;
}

int EasyTcpServer::Accept(struct sockaddr_in* _sin,socklen_t * _sinLen) const {
    if(!getSocketStatus())
    {
        printf("sock error\n");
        return -1;
    }
    int n;
    again:
    if ((n = accept(this->m_socket,(sockaddr*)&_sin,_sinLen)) < 0) {
        if ((errno == ECONNABORTED) || (errno == EINTR))//如果是被信号中断和软件层次中断,不能退出
        {
            goto again;
        }
        else
        {
            printf("连接客户端失败!\n");
            return -1;
        }
    }
    //printf("[%s:%u]上线了....\n", inet_ntoa(_sin->sin_addr), _sin->sin_port);
    return n;
}
