/*
** EPITECH PROJECT, 2021
** B-CCP-400-NAN-4-1-theplazza-victor.harri-chal
** File description:
** Globals.hpp
*/

#ifndef _GLOBALS_HPP_
    #define _GLOBALS_HPP_

    #include "MessageQueue/MessageQueue.hpp"
    #include "Log/Log.hpp"
    #include "Mutex.hpp"
    #include <vector>

    extern int *ShmPtr;
    extern std::vector<int> pizzas_per_cmd;
    extern std::vector<int> pizzas_rcv_per_cmd;
    extern std::vector<std::string> commands;
    extern int curr_pizzas;
    extern MessageQueue queue;
    extern Log logger;
    extern Mutex *m1;
    extern Mutex *m2;
    extern Mutex *m3;
    extern Mutex *m4;
    extern Mutex *m5;

#endif