#include <string>
#include <iostream>

#include <boost/serialization/string.hpp>
#include <boost/archive/text_iarchive.hpp>

#define MAX_SIZE 1000

class Message
{
    public :
        Message(std::string a_msg_header, std::string a_msg) : _msg_header(a_msg_header), _msg_body(a_msg) {};
        Message() { _msg_header = "default"; _msg_body = "default"; };
        void display()
        {
            std::cout << "message header: " << _msg_header << std::endl;
            std::cout << "message id : " << _msg_body << std::endl;
        };
    private :
        friend class boost::serialization::access;
        template <typename Archive>
        void serialize(Archive &ar, const unsigned int version)
        {
            ar &_msg_header;
            ar &_msg_body;
            std::cout << __FUNCTION__ << ", " << __LINE__ << std::endl;
        }
        std::string _msg_header; //Expects a JSON formatted string
        std::string _msg_body; // Expects a JSON formatted string
};