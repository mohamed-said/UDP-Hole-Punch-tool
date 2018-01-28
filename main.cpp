#include <iostream>
#include <csignal>

#include "HolePunchEngine.h"

using namespace std;


void signal_handler(int signo) {
    if (signo == SIGINT) {
        cout << "** Interrupt signal received ... " << endl;
        cout << "** Shutting Down threads ..." << endl;
        HolePunchEngine::get_holepunch_engine_instance()->stop_sending();
        HolePunchEngine::get_holepunch_engine_instance()->stop_receiving();
        exit(signo);
    }
    if (signo == SIGABRT) {
        cout << "Abort signal received ..." << endl;
    }
}

int main() {
    signal(SIGINT, signal_handler);
    signal(SIGABRT, signal_handler);

    const int n_recv_ports = 5;

    string server_ip = "172.19.1.27";

    uint16_t receiving_ports[n_recv_ports] = {55123, 57321, 59456, 61654, 64789};

    vector<UDPSocket> receiving_sockets(n_recv_ports);

    int i = 0;
    for (UDPSocket &sock : receiving_sockets) {
        int sock_ret = sock.init_socket();
        cout << "Socket #" << i << ":" << sock_ret << endl;
        sock.set_ip_address(server_ip);
        sock.bind_socket_to_port(receiving_ports[i++]);
    }

    HolePunchEngine::get_holepunch_engine_instance()->init_engine();
    HolePunchEngine::get_holepunch_engine_instance()->run_engine(receiving_sockets);

    return 0;
}