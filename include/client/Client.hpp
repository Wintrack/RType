/*
** EPITECH PROJECT, 2022
** B-CPP-500-MAR-5-1-rtype-theo.garnier-test-ecs
** File description:
** Client
*/

/**
 * @file Client.hpp
 * @brief System class
 * @version 0.1
 * @date 2022-10-17
 *
 */

#include "../game/Menu.hpp"
#include "../game/Lobby.hpp"
#include "../game/Macro.hpp"
#include <boost/asio.hpp>
#include "../server/serialize.hpp"
using boost::asio::ip::udp;

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

class Client {
    public:
        Client(boost::asio::io_context& io_context, char *ip, short port);
        ~Client();
        void do_receive();
        void Client_in_action();
        void Client_send(void *sended_info, size_t size);
        ser _serializer;
    protected:
    Menu *Menu_client;
    Lobby_Client *Lobby_client;
    Room_client *Room_ig;
    s_Client COUPLE;
    int check_load;
    int check_ig;
    boost::asio::io_context io_context;
    udp::endpoint sender_endpoint;
    udp::socket _s;
    int client_state;
    int16_t receive_buffer[600];
    void *send_buffer;
    udp::resolver::results_type endpoints;
    INSTRUCTION_GENERIC real_infos;
    //int client_state;
    private:
};

#endif /* !CLIENT_HPP_ */
