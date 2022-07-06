/*
** EPITECH PROJECT, 2021
** B-CCP-400-NAN-4-1-theplazza-victor.harri-chal
** File description:
** Globals.cpp
*/

#include "Globals.hpp"

int *ShmPtr;
int curr_pizzas; // total nbr of pizzas inside every kitchens
std::vector<int> pizzas_per_cmd; // total number of pizzas per command
std::vector<int> pizzas_rcv_per_cmd; // counter for the upside variable
std::vector<std::string> commands; // store every command inside it where the index of the vector = id of the commands
MessageQueue queue; // IPC message queue, reception to kitchen and kitchen to reception
Log logger; // the logger to write commands and finished commands into a file
Mutex *m1;
Mutex *m2;
Mutex *m3;
Mutex *m4;
Mutex *m5;