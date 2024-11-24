/*
** EPITECH PROJECT, 2022
** B-CPP-500-MAR-5-1-rtype-theo.garnier
** File description:
** serialize.cpp
*/

/**
 * @file serialize.cpp
 * @brief serialize function
 * @version 0.1
 * @date 2022-10-17
 *
 */


#include "serialize.hpp"

ser::ser()
{
}

ser::~ser()
{
}

void ser::serialize(INSTRUCTION_GENERIC ins)
    {
    std::cout << "SERIALIZE" << std::endl;
    std::vector<int16_t> tmp;
    tmp.push_back(ins.instruction);
    tmp.push_back(CHAMP_DELIMITER);
    for (int16_t i = 0; i != ins.rooms_in_lobby.size(); i++) {
        for (int16_t y = 0; y != ins.rooms_in_lobby.at(i).size(); y++) {
            ins.rooms_in_lobby.at(i).at(y);
            tmp.push_back(ins.rooms_in_lobby.at(i).at(y));
        }
        tmp.push_back(VAR_DELIMITER);
    }
    tmp.push_back(CHAMP_DELIMITER);
    for (int16_t i = 0; i != ins.maxpl.size(); i++) {
        tmp.push_back(ins.maxpl.at(i));
        tmp.push_back(VAR_DELIMITER);
    }
    tmp.push_back(CHAMP_DELIMITER);
    for (int16_t y = 0; y != ins.name_room_created.size() ; y++) {
            tmp.push_back(ins.name_room_created.at(y));
    }
    tmp.push_back(CHAMP_DELIMITER);
        for (int16_t y = 0; y != ins.name_selected.size() ; y++) {
            tmp.push_back(ins.name_selected.at(y));
    }
    tmp.push_back(CHAMP_DELIMITER);
    for (int16_t i = 0; i != ins.RAM_DATABASE.size(); i++) {
        tmp.push_back(ins.RAM_DATABASE.at(i).type);
        tmp.push_back(ins.RAM_DATABASE.at(i).underType);
        tmp.push_back(ins.RAM_DATABASE.at(i).id);
        std::cout << "ID de " << i << " = " << ins.RAM_DATABASE.at(i).id << std::endl;
        tmp.push_back(ins.RAM_DATABASE.at(i).health);
        tmp.push_back(ins.RAM_DATABASE.at(i).pos_y);
        tmp.push_back(ins.RAM_DATABASE.at(i).pos_x);
        tmp.push_back(ins.RAM_DATABASE.at(i).frame);
        tmp.push_back(ins.RAM_DATABASE.at(i).damage);
        tmp.push_back(VAR_DELIMITER);
    }
    tmp.push_back(CHAMP_DELIMITER);
    for (int16_t i = 0; i != ins.info_player.size(); i++) {
        tmp.push_back(ins.info_player.at(i));
        tmp.push_back(VAR_DELIMITER);
    }
    tmp.push_back(CHAMP_DELIMITER);
    int16_t tmp_int16_t = 0;
    int16_t i = 0;
    for (i = 0; i < tmp.size(); i++) {
        tmp_int16_t = tmp.at(i);
        buffer[i] = tmp_int16_t;
    }
    buffer[i] = END_DATA;
    }


INSTRUCTION_GENERIC ser::deserialize(int16_t *buffer)
    {
        std::cout << "DESERIALIZE" << std::endl;
        INSTRUCTION_GENERIC ins;
    std::vector<std::vector<std::vector<int16_t>>> all_buffer;
    std::vector<std::vector<int16_t>> champ_tmp;
    std::vector<int16_t> var_tmp;
    int16_t champ_count;
    for (int16_t i = 0; buffer[i] != END_DATA; i++) {
        if (buffer[i] == -1) {
            std::cout << "-1" << std::endl;
            if (champ_tmp.size() != 0) {
                all_buffer.push_back(champ_tmp);
                champ_tmp.clear();
                var_tmp.clear();
            }
            else {
                champ_tmp.push_back(var_tmp);
                all_buffer.push_back(champ_tmp);
                champ_tmp.clear();
                var_tmp.clear();
            }
        }
        else if (buffer[i] == -2) {
            std::cout << "-2" << std::endl;
            champ_tmp.push_back(var_tmp);
            var_tmp.clear();
        }
        else {
            //std::cout << "buffer[i] = " << buffer[i] << std::endl;
            var_tmp.push_back(buffer[i]);
            }
        }
    for(int16_t buffer_row = 0; buffer_row != all_buffer.size(); buffer_row++) {
        std::string tmp;
        int16_t tmp_max;
        std::vector<std::string> name_rooms;
        std::vector<int16_t> max;
        std::vector<s_Entity> vec_en;
        s_Entity tmp_en;
        switch (buffer_row)
        {
        case 0:
            ins.instruction = all_buffer.at(0).at(0).at(0);
            break;
        case 1:
            for (int16_t champ_row = 0; champ_row != all_buffer.at(buffer_row).size();  champ_row++) {
                for (int16_t var_row = 0; var_row != all_buffer.at(buffer_row).at(champ_row).size(); var_row++) {
                    tmp.push_back(all_buffer.at(buffer_row).at(champ_row).at(var_row));
                }
                name_rooms.push_back(tmp);
                tmp.clear();
            }
            ins.rooms_in_lobby= name_rooms;
            tmp.clear();
            break;
        case 2:
            for (int16_t champ_row = 0; champ_row != all_buffer.at(buffer_row).size();  champ_row++) {
                for (int16_t var_row = 0; var_row != all_buffer.at(buffer_row).at(champ_row).size(); var_row++) {
                    tmp_max = all_buffer.at(buffer_row).at(champ_row).at(var_row);
                }
                max.push_back(tmp_max);
                tmp.clear();
            }
            ins.maxpl = max;
            tmp.clear();
            max.clear();
            break;
        case 3:
            for (int16_t champ_row = 0; champ_row != all_buffer.at(buffer_row).size();  champ_row++) {
                for (int16_t var_row = 0; var_row != all_buffer.at(buffer_row).at(champ_row).size(); var_row++) {
                    tmp.push_back(all_buffer.at(buffer_row).at(champ_row).at(var_row));
                }
            }
            ins.name_room_created = tmp;
            break;
        case 4:
            for (int16_t champ_row = 0; champ_row != all_buffer.at(buffer_row).size(); champ_row++) {
                for (int16_t var_row = 0; var_row != all_buffer.at(buffer_row).at(champ_row).size(); var_row++) {
                    tmp.push_back(all_buffer.at(buffer_row).at(champ_row).at(var_row));
                }
            }
            ins.name_selected = tmp;
            break;
        case 5:
            for (int16_t champ_row = 0; champ_row != all_buffer.at(buffer_row).size();  champ_row++) {
                if (all_buffer.at(buffer_row).at(champ_row).size() != 0) {
                    tmp_en.type = all_buffer.at(buffer_row).at(champ_row).at(0);
                    std::cout << "VALUED 1" << std::endl;
                    tmp_en.underType = all_buffer.at(buffer_row).at(champ_row).at(1);
                    std::cout << "VALUED2" << std::endl;
                    tmp_en.id = all_buffer.at(buffer_row).at(champ_row).at(2);
                    std::cout << "ID de " << buffer_row << " = " << all_buffer.at(buffer_row).at(champ_row).at(2) << std::endl;
                    std::cout << "VALUED 3" << std::endl;
                    tmp_en.health = all_buffer.at(buffer_row).at(champ_row).at(3);
                    std::cout << "VALUED 4" << std::endl;
                    tmp_en.pos_y = all_buffer.at(buffer_row).at(champ_row).at(4);
                    std::cout << "VALUED 5" << std::endl;
                    tmp_en.pos_x = all_buffer.at(buffer_row).at(champ_row).at(5);
                    std::cout << "VALUED posX" << std::endl;
                    tmp_en.frame = all_buffer.at(buffer_row).at(champ_row).at(6);
                    std::cout << "VALUED FRAM" << std::endl;
                    tmp_en.damage = all_buffer.at(buffer_row).at(champ_row).at(7);
                    std::cout << "VALUED DAMAGE" << std::endl;
                    vec_en.push_back(tmp_en);
                }
            }
            ins.RAM_DATABASE = vec_en;
            break;
        case 6:
            std::cout << "INFO_PLAYER" << std::endl;
            for (int16_t champ_row = 0; champ_row != all_buffer.at(buffer_row).size();  champ_row++) {
                for (int16_t var_row = 0; var_row != all_buffer.at(buffer_row).at(champ_row).size(); var_row++) {
                    tmp_max = all_buffer.at(buffer_row).at(champ_row).at(var_row);
                }
                max.push_back(tmp_max);
                tmp.clear();
            }
            ins.info_player = max;
            tmp.clear();

            std::cout << "INFO_PLAYER FIN" << std::endl;
            break;
        default:
            break;
        }
        std::cout << "TOUR DE BOUCLE DESER" << std::endl;
    }
    buffer = NULL;
    std::cout << "_____________fin deserialize____________" << std::endl;
    return (ins);
    };