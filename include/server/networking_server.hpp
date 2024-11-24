/*
** EPITECH PROJECT, 2022
** B-CPP-500-MAR-5-1-rtype-theo.garnier
** File description:
** networking_server
*/



#include "server/serialize.hpp"
#include "../game/Macro.hpp"

class UDP_Server
{
public:
    UDP_Server(boost::asio::io_context &io_context, short port);
    void do_receive();
    // void do_send();
    void do_send_specific(udp::endpoint sender_endpoint);

private:

    void get_endpoint(udp::endpoint sender_endpoint);

    udp::socket socket_;
    udp::endpoint sender_endpoint_;
    enum
    {
        max_length = 1024
    };
    char data_[max_length];

    std::vector<udp::endpoint> _clients;
    serialize<INSTRUCTION_GENERIC> _ser;
};
