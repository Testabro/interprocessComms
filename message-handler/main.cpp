
#include <vector>
#include <iostream>
#include <string>
#include <boost/interprocess/ipc/message_queue.hpp>

//#include "neuron.h"
#include "message-handler.h"
using namespace boost::interprocess;


std::unique_ptr<MessageHandler> init() {        

    auto msg_handler = std::make_unique<MessageHandler>();   
    Neuron n2tx("mq1", "tx");
    Neuron n2rx("mq1", "rx");

    msg_handler->add_neuron(std::move(n2tx));
    msg_handler->add_neuron(std::move(n2rx));
    
    message_queue::remove("mq0");
    message_queue::remove("mq1");

    return msg_handler;
}


int main(int argc, char *argv[]) {
    //MessageHandler msg_handler;
    auto msg_handler = init();

    if(std::string(argv[1]) == "rx" ) {
        std::cout << "RX" << std::endl;

        while(true) {
            msg_handler->_mq_map["rxmq1"].read_msg();
            sleep(1);
        }
    } 

    if(std::string(argv[1]) == "tx" ) {
        std::cout << "TX" << std::endl;
        while(true) {
            std::string header;
            std::string body;
            std::cin >> header;
            std::cin >> body;
            Message test(header, body);

            msg_handler->_mq_map["txmq1"].send_msg(test);
            std::cin.get();
        }
    }
       
}