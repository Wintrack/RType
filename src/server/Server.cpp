/*
** EPITECH PROJECT, 2022
** B-CPP-500-MAR-5-1-rtype-theo.garnier-test-ecs
** File description:
** Server
*/

/**
 * @file Server.cpp
 * @brief Server function
 * @version 0.1
 * @date 2022-10-17
 *
 */


#include "../../include/server/Server.hpp"

Server::Server(boost::asio::io_context &io_context, short port) : socket_(io_context, udp::endpoint(udp::v4(), port))
{
    lobby.add_new_room("Room 1", 4);
    lobby.add_new_room("Room 2", 4);
    lobby.add_new_room("Room 3", 4);
    do_receive();
    index_player = 0;
}

Server::~Server()
{
}

void Server::get_endpoint(udp::endpoint sender_endpoint)
{
    if (std::find(_clients.begin(), _clients.end(), sender_endpoint) == _clients.end())
        _clients.push_back(sender_endpoint);
}

std::vector<std::string> get_lobby_names(Lobby_Serv lobby)
{
    int i = 0;
    std::vector<std::string> tmp;
    while (i != lobby.rooms_on_list.size())
    {
        tmp.push_back(lobby.rooms_on_list.at(i)->room_name);
        i++;
    }
    return tmp;
}

std::vector<int16_t> get_lobby_maxpl(Lobby_Serv lobby)
{
    int i = 0;
    std::vector<int16_t> tmp;
    while (i != lobby.rooms_on_list.size())
    {
        tmp.push_back(lobby.rooms_on_list.at(i)->max_players);
        i++;
    }
    return tmp;
}

void Server::do_receive()
{
    socket_.async_receive_from(
        boost::asio::buffer(&buffer, sizeof(buffer)), sender_endpoint_,
        [this](boost::system::error_code ec, std::size_t bytes_recvd)
        {
            std::cout << "CLIENT RECEIVE" << std::endl;
            int elu = -1;
            if (!ec && bytes_recvd > 0)
            {
                //memset(&created_datas, 0, sizeof(created_datas));
                extracted_datas = _serialize.deserialize(buffer);
                switch (extracted_datas.instruction)
                {
                case JOIN_LOBBY_INS:
                    created_datas.instruction = JOINED_LOBBY;
                    created_datas.rooms_in_lobby = get_lobby_names(lobby);
                    created_datas.maxpl = get_lobby_maxpl(lobby);
                    break;
                case JOIN_ROOM:
                    created_datas.instruction = JOINED_ROOM;
                    std::cout << "INSTRUCTION DEBUT: " << created_datas.instruction;
                    for (int i = 0; i < (lobby.rooms_on_list.size() - 1); i++) {
                        std::cout << "i : " << i << std::endl;
                        if (extracted_datas.name_selected == lobby.rooms_on_list.at(i)->room_name) {
                            elu = i;
                        }
                    }
                    std::cout << "elu = " << elu << std::endl;
                    if (elu != -1) {
                        std::cout << "PRINT IF ELU" << std::endl;
                        if (lobby.rooms_on_list.at(elu)->clients_in_game.size() != 0) {
                            lobby.rooms_on_list.at(elu)->Add_client(sender_endpoint_);
                            created_datas.info_player.push_back(lobby.rooms_on_list.at(elu)->Game->CLIENT_IDS.at(index_player));
                            created_datas.RAM_DATABASE = lobby.rooms_on_list.at(elu)->Game->getRam();
                            index_player++;
                        }
                        else {
                            lobby.rooms_on_list.at(elu)->Create_room(sender_endpoint_, 0);
                            created_datas.info_player.push_back(lobby.rooms_on_list.at(elu)->Game->CLIENT_IDS.at(0));
                            created_datas.RAM_DATABASE = lobby.rooms_on_list.at(elu)->Game->getRam();
                            index_player++;
                        }
                    }
                    break;
                case JOINED_GAME:
                    std::cout << "JOINED_GAMEEEEEEEEEEEEEEEEEEEEEEEEEE" << std::endl;
                    for (int i = 0; i < (lobby.rooms_on_list.size() - 1); i++) {
                        std::cout << "i : " << i << std::endl;
                        if (extracted_datas.name_selected == lobby.rooms_on_list.at(i)->room_name) {
                            elu = i;
                        }
                    }
                    std::cout << "PASSED 1" << std::endl;
                    //std::cout << "BUG: " << lobby.rooms_on_list.at(elu)->Game->CLIENT_IDS.at(0) << std::endl;
                    if (elu != -1) {
                        int id_index = 0;
                        created_datas.info_player.clear();
                        std::cout << "PASSED 2" << std::endl;
                        lobby.rooms_on_list.at(elu)->Treating_Game_Loop(extracted_datas.info_player.at(0), extracted_datas.info_player.at(1),
                                                                               extracted_datas.info_player.at(2), extracted_datas.info_player.at(3));
                        std::cout << "PASSED 3" << std::endl;
                        if (lobby.rooms_on_list.at(elu)->change_level != 0) {
                            lobby.rooms_on_list.at(elu)->Game->CLIENT_IDS.clear();
                            lobby.rooms_on_list.at(elu)->Create_room(sender_endpoint_, lobby.rooms_on_list.at(elu)->index_level);
                            created_datas.info_player.push_back(lobby.rooms_on_list.at(elu)->Game->CLIENT_IDS.at(0));
                            lobby.rooms_on_list.at(elu)->change_level = 0;
                        }
                        created_datas.RAM_DATABASE = lobby.rooms_on_list.at(elu)->Game->getRam();
                        if (lobby.rooms_on_list.at(elu)->lose == 1) {
                            created_datas.instruction = EXIT_CLIENT_INS;
                            std::cout << "END OF THE GAME: \t LOSE :"<< lobby.rooms_on_list.at(elu)->lose << std::endl;
                            created_datas.rooms_in_lobby = get_lobby_names(lobby);
                            created_datas.maxpl = get_lobby_maxpl(lobby);
                            created_datas.RAM_DATABASE.clear();
                            lobby.rooms_on_list.at(elu)->lose = 0;
                            lobby.rooms_on_list.at(elu)->clients_in_game.clear();
                            lobby.rooms_on_list.at(elu)->Game->DATABASE.clear();
                            lobby.rooms_on_list.at(elu)->Game->RAM_DATABASE.clear();
                            lobby.rooms_on_list.at(elu)->Game->CLIENT_IDS.clear();
                            lobby.rooms_on_list.at(elu)->change_level = 0;
                            lobby.rooms_on_list.at(elu)->index_level = 0;
                            index_player = 0;
                        }
                        std::cout << "SIZE DATABASE = " << created_datas.RAM_DATABASE.size() << std::endl;
                        for (int i = 0; i < lobby.rooms_on_list.at(elu)->clients_in_game.size(); i++)
                        {
                            if (lobby.rooms_on_list.at(elu)->clients_in_game.at(i) == sender_endpoint_) {
                                created_datas.info_player.clear();
                                created_datas.info_player.push_back(lobby.rooms_on_list.at(elu)->Game->CLIENT_IDS.at(id_index));
                                do_send_specific(lobby.rooms_on_list.at(elu)->clients_in_game[i]);
                            }
                            else {
                                created_datas.info_player.clear();
                                created_datas.info_player.push_back(lobby.rooms_on_list.at(elu)->Game->CLIENT_IDS.at(i));
                                do_send_specific(lobby.rooms_on_list.at(elu)->clients_in_game[i]);
                            }
                        }
                        do_receive();
                    }
                    break;
                default:
                    break;
                }
                elu = -1;
                get_endpoint(sender_endpoint_);
                std::cout << "INSTRUCTION FIN: " << created_datas.instruction;
                do_send_specific(sender_endpoint_);
                created_datas.info_player.clear();
                do_receive();
            }
            else
            {
                do_receive();
            }
            //usleep(1667);
        });
}

// polymorphique
void Server::do_send_specific(udp::endpoint sender_endpoint)
{
    int data_to_send = sizeof(created_datas);
    _serialize.serialize(created_datas);
    for (int i = 0; _serialize.buffer[i] != END_DATA; i++)
        std::cout << "buffer[" << i << "] = " << buffer[i] << std::endl;
    socket_.async_send_to(boost::asio::buffer(_serialize.buffer, sizeof(_serialize.buffer)), sender_endpoint,
                          [this](boost::system::error_code, std::size_t)
                          {
                              std::cout << "sending" << std::endl;
                          });
}
// void UDP_Server::do_send()
// {
//     std::cout << "Enter message (server): ";
//     std::cin.getline(data_, max_length);

//     size_t length = strlen(data_);

//     socket_.async_send_to(boost::asio::buffer(data_, length), sender_endpoint_,
//                           [this](boost::system::error_code, std::size_t)
//                           {
//                               do_receive();
//                           });
// }