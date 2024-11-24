/*
** EPITECH PROJECT, 2022
** B-CPP-500-MAR-5-1-rtype-theo.garnier-main
** File description:
** ser
*/
#include <iostream>
#include <sstream>
#include <ostream>
#include "Macro.hpp"
#include <cstdlib>
#include <boost/config.hpp>


#ifndef SER_HPP_
#define SER_HPP_

class ser
{
private:
public:
    int16_t buffer[1000];
    int16_t deser_buffer[1000];
    ser();
    ~ser();
    INSTRUCTION_GENERIC deserialize(int16_t *buffer);
    void serialize(INSTRUCTION_GENERIC ins);
};

#endif /* !SER_HPP_ */