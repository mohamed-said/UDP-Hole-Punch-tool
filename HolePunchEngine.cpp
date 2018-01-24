//
// Created by kogo on 1/22/18.
//

#include "HolePunchEngine.h"

HolePunchEngine* HolePunchEngine::holePunchEngineInstance = nullptr;

HolePunchEngine::HolePunchEngine() = default;

HolePunchEngine::~HolePunchEngine() {
    if (recv_threads != nullptr) {
        delete []recv_threads;
        recv_threads = nullptr;
    }

    if (holePunchEngineInstance != nullptr) {
        delete holePunchEngineInstance;
        holePunchEngineInstance = nullptr;
    }

}

void HolePunchEngine::init_engine() {
    m_stop_sending = false;
    m_stop_receiving = false;
}

void HolePunchEngine::stop_sending() {
    m_stop_sending = true;
}

void HolePunchEngine::stop_receiving() {
    m_stop_receiving = true;
}

bool HolePunchEngine::sending_state() const {
    return m_stop_sending;
}

bool HolePunchEngine::receiving_state() const {
    return m_stop_receiving;
}

HolePunchEngine* HolePunchEngine::get_holepunch_engine_instance() {
    if (holePunchEngineInstance == nullptr) {
        holePunchEngineInstance = new HolePunchEngine;
    }
    return holePunchEngineInstance;
}

void __run_sending(vector<UDPSocket> &receiving_sockets) {

    char buffer[11] = {0};
    memccpy(buffer, "send punch", 0, 11);

    while (!HolePunchEngine::get_holepunch_engine_instance()->sending_state()) {
        for (UDPSocket sock : receiving_sockets) {
            sock.send_udp(&buffer, 11);
        }
    }
    cout << "\t** Exiting sending thread..." << endl;
}

void __run_receiving(UDPSocket *udp_socket) {
    char buffer[11] = {0};
    size_t buff_length = 11;
    while (!HolePunchEngine::get_holepunch_engine_instance()->receiving_state()) {
        udp_socket->recv_udp(&buffer, buff_length);
        sockaddr_in client_data = udp_socket->get_client_data();
        cout << inet_ntoa(client_data.sin_addr) << ":" << ntohs(client_data.sin_port) << " sent: " << buffer << endl;
        cout << buffer << endl;
        memset(buffer, 0, 11);
    }
    cout << "\t** Exiting receiving thread..." << endl;
}

void HolePunchEngine::run_engine(vector<UDPSocket> &receiving_sockets) {

    thread send_t = thread(__run_sending, receiving_sockets);
    send_t.join();

    const ulong recv_socks = receiving_sockets.size();

    recv_threads = new thread[recv_socks];

    for (int i = 0; i < recv_socks; i++) {
        recv_threads[i] = thread(__run_receiving, &receiving_sockets[i]);
        recv_threads[i].join();
    }
}