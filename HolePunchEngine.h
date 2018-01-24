//
// Created by kogo on 1/22/18.
//

#ifndef UDP_HOLEPUNCH_TOOL_HOLEPUNCHENGINE_H
#define UDP_HOLEPUNCH_TOOL_HOLEPUNCHENGINE_H

#include <thread>
#include <vector>
#include "UDPSocket.h"

using std::thread;
using std::cout;
using std::endl;
using std::vector;

class HolePunchEngine {

private:

    bool m_stop_sending;
    bool m_stop_receiving;
    thread *recv_threads;

    static HolePunchEngine *holePunchEngineInstance;
    HolePunchEngine();

public:

    HolePunchEngine(const HolePunchEngine&) = delete;
    ~HolePunchEngine();

    void init_engine();
    void run_engine(vector<UDPSocket>&);

    void stop_sending();
    void stop_receiving();

    bool sending_state() const;
    bool receiving_state() const;

    static HolePunchEngine* get_holepunch_engine_instance();
};


#endif //UDP_HOLEPUNCH_TOOL_HOLEPUNCHENGINE_H
