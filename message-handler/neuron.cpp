#include <string>
#include <sstream>
#include <iostream>

#include <boost/interprocess/ipc/message_queue.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#include "neuron.h"

using namespace boost::interprocess;


void Neuron::send_msg(Message msg) {
  if(_type == "tx") {
    try {
    //Create a message_queue.
    message_queue msg_queue
      (open_or_create //create only
      ,_mq_name.c_str() //name
      ,1 //max message number
      //,sizeof(smessage) //max message size
      ,MAX_SIZE
    );
    // task to send message
    std::stringstream oss;
    boost::archive::text_oarchive oa(oss);
    oa << msg; // serilize the message to oss buffer
    std::string serialized_string(oss.str()); // send message by message queue with string buffer
    msg_queue.send(serialized_string.data(), serialized_string.size(), 0);
    }
    catch(interprocess_exception &ex)
    {  
        std::cerr << ex.what() << std::endl;
    }
  }  
};

Message Neuron::read_msg() {
  //Init Message
  Message msg("something went wrong","something went wrong");
  if(_type == "rx") {
    try
    {
        //Create a message_queue. This is a shared mem object and is NOT destoryed when this scope of this metho is left; calling class is responsible to clean up this queue
        message_queue mq(
            open_only //create only
            ,_mq_name.c_str() //name
        );
        // task receiving message from above task
        unsigned int priority;
        message_queue::size_type recvd_size;

        std::stringstream iss;
        std::string serialized_string;
        serialized_string.resize(MAX_SIZE);
        mq.receive(&serialized_string[0], MAX_SIZE, recvd_size, priority);
        serialized_string.resize(recvd_size);
        iss << serialized_string; // save received serialized data to streamstring buffer
        boost::archive::text_iarchive ia(iss);
        ia >> msg; // de-serialization received data
        msg.display();
        return msg;
    }
    catch(interprocess_exception &ex)
    {  
        std::cerr << ex.what() << std::endl;
    }
  }
  return msg;
};