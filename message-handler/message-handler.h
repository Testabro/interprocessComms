
#include <vector>

#include "neuron.h"

class MessageHandler {
    public:
        std::unordered_map<std::string, Neuron> _mq_map; //keep ownership of all neurons for this process
        MessageHandler() {};
        void add_neuron(Neuron neuron);

        int msg_q_count() { return _mq_map.size(); };  // Inialize process
    private:
        int _pid = 0; // This processes process id        
};