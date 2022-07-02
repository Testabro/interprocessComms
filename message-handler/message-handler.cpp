#include "message-handler.h"

void MessageHandler::add_neuron(Neuron neuron) {
    _mq_map.insert({neuron.get_type() + neuron.get_msg_q_name() ,neuron});
}
