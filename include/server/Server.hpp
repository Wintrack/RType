/*
** EPITECH PROJECT, 2022
** B-CPP-500-MAR-5-1-rtype-theo.garnier-test-ecs
** File description:
** Server
*/
#include <iostream>
#include <vector>
#include "../game/Lobby.hpp"
#include "Room.hpp"
#include "serialize.hpp"
#include <cstdlib>
#include <iostream>
#include <boost/asio.hpp>
#include <vector>
using boost::asio::ip::udp;
#ifndef SERVER_HPP_
#define SERVER_HPP_

class Server {
    public:
        Server(boost::asio::io_context &io_context, short port);
        ~Server();
    protected:
        void do_receive();
        void do_send_specific(udp::endpoint sender_endpoint);
        void get_endpoint(udp::endpoint sender_endpoint);
        udp::socket socket_;
        udp::endpoint sender_endpoint_;
        void *receive_buffer;
        INSTRUCTION_GENERIC created_datas;
        INSTRUCTION_GENERIC extracted_datas;
        std::vector<udp::endpoint> _clients;
        ser _serialize;
        int index_player;
        int16_t buffer[600];
    private:
        Lobby_Serv lobby;
        std::vector<s_Client> clients_online;
};

#endif /* !SERVER_HPP_ */
