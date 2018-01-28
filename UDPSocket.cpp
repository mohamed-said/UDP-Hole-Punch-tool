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

uint16_t UDPSocket::get_port() const {
	return ntohs(sa.sin_port);
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
    sa.sin_addr.s_addr = INADDR_ANY;
    int bind_error = bind(socket_fd, (sockaddr*) &sa, sizeof(sa));
    return bind_error;
}

ssize_t UDPSocket::send_udp(const void *__buffer, size_t __len, uint16_t dest_port) {
	send_sa.sin_family = AF_INET;
	hostent *server = gethostbyname("172.19.1.27");
	bcopy((char*)server->h_addr, (char*)&send_sa.sin_addr.s_addr, server->h_length);
    cout << "Destination port: " << endl;
	send_sa.sin_port = htons(dest_port);
	cout << "Sending Message to: " << inet_ntoa(send_sa.sin_addr) << ":" << ntohs(send_sa.sin_port) << endl;
    ssize_t send_error = sendto(socket_fd, __buffer, __len, 0, (sockaddr*) &send_sa, sizeof(send_sa));
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
