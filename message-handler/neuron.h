#include <string>

#include "../message.hpp"

// A Neuron is expected to be used either as a send or receive
class Neuron {
  public:
    Neuron() { _mq_name = "default"; _type = "rx"; };
    Neuron(std::string a_mq_name, std::string a_type) { _mq_name = a_mq_name; _type = a_type;};
    Message read_msg(); // Read a JSON formatted message off of the message bus this object is subscribed to
    void send_msg(Message _msg); // Send a JSON formatted message off of the message bus this object is subscribed to
    std::string get_msg_q_name(){ return _mq_name; };
    std::string get_type(){ return _type; };
  private:
    std::string _mq_name;
    std::string _type; // Specify whether this neuron is a send node or receive node
    int weight;
    int bias;
};