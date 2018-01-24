//
// Created by kogo on 1/22/18.
//

#include "UDPSocket.h"


UDPSocket::UDPSocket() {
    memset((void*) &sa, 0, sizeof(sa));
    memset((void*) &dest_sa, 0, sizeof(dest_sa));
}

int UDPSocket::init_socket() {
    socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
    return socket_fd;
}

int UDPSocket::get_socket_handle() const {
    return socket_fd;
}

void UDPSocket::set_socket_handle(int __socket_fd) {
    socket_fd = __socket_fd;
}

void UDPSocket::set_ip_address(const string &__ipv4) {
    ipv4 = __ipv4;
}

int UDPSocket::bind_socket_to_port(uint16_t port) {
    sa.sin_family = AF_INET;
    sa.sin_port = htons(port);
    sa.sin_addr.s_addr = htonl(inet_addr(ipv4.c_str()));
    int bind_error = bind(socket_fd, (sockaddr*) &sa, sizeof(sa));
    return bind_error;
}

ssize_t UDPSocket::send_udp(const void *__buffer, size_t __len) {
    ssize_t send_error = sendto(socket_fd, __buffer, __len, 0, (sockaddr*) &sa, sizeof(sa));
    return send_error;
}

ssize_t UDPSocket::recv_udp(void *__buffer, size_t &__len) {
    socklen_t addrlen;
    ssize_t recv_error = recvfrom(socket_fd, __buffer, __len, 0, (sockaddr*) &dest_sa, &addrlen);
    return recv_error;
}

sockaddr_in UDPSocket::get_client_data() {
    return dest_sa;
}

UDPSocket::~UDPSocket() {
    close(socket_fd);
}
