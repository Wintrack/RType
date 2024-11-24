/*
** EPITECH PROJECT, 2022
** B-CPP-500-MAR-5-1-rtype-theo.garnier
** File description:
** main
*/

/**
 * @file ClientInternalLogic.cpp
 * @brief Fire class
 * @version 0.1
 * @date 2022-10-17
 *
 */


#include "server/Server.hpp"
 #include <iostream>

int main(int argc, char *argv[])
{
    try
    {
        if (argc != 2)
        {
            std::cerr << "Usage: r-type_server <port>\n";
            return 1;
        }

        boost::asio::io_context io_context;
        Server s(io_context, std::atoi(argv[1]));

        io_context.run();
    }
    catch (std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}