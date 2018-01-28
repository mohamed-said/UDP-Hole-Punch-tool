//
// Created by kogo on 1/22/18.
//

#ifndef UDP_HOLEPUNCH_TOOL_UDPSOCKET_H
#define UDP_HOLEPUNCH_TOOL_UDPSOCKET_H

#include <iostream>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <cstring>
#include <unistd.h>

using std::string;
using std::cout;
using std::endl;

class UDPSocket {

private:

    int socket_fd;
    sockaddr_in sa;
    sockaddr_in dest_sa;
    sockaddr_in send_sa;
    string ipv4;

public:

    UDPSocket();
    ~UDPSocket();
    void set_socket_handle(int __socket_fd);
    void set_ip_address(const string &__ipv4);
    int get_socket_handle() const;
    int get_port() const;
    int init_socket();
    int bind_socket_to_port(uint16_t port);
    ssize_t send_udp(const void *__buffer, size_t __len, int);
    ssize_t recv_udp(void *__buffer, size_t &__len);
    sockaddr_in get_client_data();

};


#endif //UDP_HOLEPUNCH_TOOL_UDPSOCKET_H
