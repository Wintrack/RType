/*
** EPITECH PROJECT, 2022
** B-CPP-500-MAR-5-1-rtype-theo.garnier-test-ecs
** File description:
** Client
*/

/**
 * @file main.cpp
 * @brief Client function + main function of client
 * @version 0.1
 * @date 2022-10-17
 *
 */

#include "../../include/client/Client.hpp"
#include "../../include/game/Macro.hpp"
using boost::asio::ip::udp;

Client::Client(boost::asio::io_context &io_context, char *ip, short port) : _s(io_context, udp::endpoint(udp::v4(), 0))
{
    check_load = 0;
    client_state = 1;
    check_ig = 0;
    udp::resolver resolver(io_context);
    int porty = port;
    std::string s = std::to_string(porty);
    char const *pchar = s.c_str();
    endpoints =
        resolver.resolve(udp::v4(), ip, pchar);

    do_receive();
}

Client::~Client()
{
    _s.close(); // fermeture du socket
}

void Client::do_receive()
{ // nouvelle fonction do_receive contenant tout ce qu'il y avait dans boucle de client_in_action avant
    _s.async_receive_from(
        boost::asio::buffer(&receive_buffer, sizeof(receive_buffer)), sender_endpoint,
        [this](boost::system::error_code ec, std::size_t bytes_recvd)
        {
            if (!ec && bytes_recvd > 0)
            {
                std::cout << "CLIENT RECEIVE" << std::endl;
                real_infos = _serializer.deserialize(receive_buffer);
                switch (real_infos.instruction)
                {
                case JOINED_LOBBY:
                    client_state = JOINED_LOBBY;
                    break;
                case JOINED_ROOM:
                std::cout << "ouaiiiiiiiiiiiiiiis" << std::endl;
                    client_state = JOINED_ROOM;
                    break;
                case EXIT_CLIENT_INS:
                    client_state = EXIT_CLIENT_INS;
                    break;
                default:
                    break;
                }
                do_receive();
            }
            else
            {
                do_receive();
            }
        });
}

void Client::Client_send(void *sended_data, size_t size)
{
}

void Client::Client_in_action()
{
    InitWindow(1920, 1080, "RAY-TYPE");
    InitAudioDevice();
    Sound music = LoadSound("assets/sprites/Cosmic-Switchboard_Looping.mp3");
    Menu_client = new Menu();
    while (!WindowShouldClose())
    {
        // Mettre graphique ici
        if (client_state == 1)
        {
            Menu_client->Menu_page();
            if (Menu_client->SENDED_INFO.instruction == 0)
            {
                _serializer.serialize(Menu_client->SENDED_INFO);
                for (int i = 0; _serializer.buffer[i] != -3; i++) {
                    std::cout << "_serializer.buffer[" << i << "] = " << _serializer.buffer[i] << std::endl;
                }
                _s.send_to(boost::asio::buffer(_serializer.buffer, sizeof(_serializer.buffer)), *endpoints.begin());
                Menu_client->SENDED_INFO.instruction = 1;
            }
        }
        if (client_state == JOINED_LOBBY)
        {
            if (check_load == 0)
            {
                Menu_client->~Menu();
                Lobby_client = new Lobby_Client(real_infos.rooms_in_lobby, real_infos.maxpl);
            }
            else
            {
                Lobby_client->Lobby_page();
                if (Lobby_client->SENDED_INFO.instruction == JOIN_ROOM)
                {
                    std::cout << "IF LOBBY CLI" << std::endl; 
                    _serializer.serialize(Lobby_client->SENDED_INFO);
                    std::cout << _s.send_to(boost::asio::buffer(_serializer.buffer, sizeof(_serializer.buffer)), *endpoints.begin()) << std::endl;
                    Lobby_client->SENDED_INFO.instruction = 6;
                }
            }
            check_load++;
        }
        if (client_state == JOINED_ROOM)
        {
            check_load = 0;
            if (check_ig == 0)
            {
                Lobby_client->~Lobby_Client();
                std::cout << "TEST1" << std::endl;
                Room_ig = new Room_client(real_infos.RAM_DATABASE, real_infos.info_player.at(0));
                std::cout << "TEST2" << std::endl;
                std::cout << "ID 1TIME :" << real_infos.info_player.at(0) << std::endl;
                PlaySound(music);
                check_ig++;
            }
            else
            {
                std::cout << "ID 2TIME :" << real_infos.info_player.at(0) << std::endl;
                Room_ig->Room_read_from_server(real_infos.RAM_DATABASE, real_infos.info_player.at(0));
                INSTRUCTION_GENERIC tmpdb = Room_ig->Renders->getInfos();
                tmpdb.name_selected = Lobby_client->SENDED_INFO.name_selected;
                _serializer.serialize(tmpdb);
                _s.send_to(boost::asio::buffer(_serializer.buffer, sizeof(_serializer.buffer)), *endpoints.begin());
            }
        }
        if (client_state == EXIT_CLIENT_INS) {
            INSTRUCTION_GENERIC tmp;
            tmp.instruction = 0;
            _serializer.serialize(tmp);
            _s.send_to(boost::asio::buffer(_serializer.buffer, sizeof(_serializer.buffer)), *endpoints.begin());
        }
    }
    CloseWindow();
    exit(0);
}

int main(int argc, char const *argv[])
{
    boost::asio::io_context io_context; // maintenant créé en dehors de la class
    Client *client = new Client(io_context, (char *)argv[1], std::atoi(argv[2]));
    std::thread network_thread([&io_context]() { // io_context run sur son propre thread
        io_context.run();
    });
    client->Client_in_action();
    delete (client);       // close de la socket
    network_thread.join(); // on attends que le thread soit fini pour fermer le programme
    return 0;
}