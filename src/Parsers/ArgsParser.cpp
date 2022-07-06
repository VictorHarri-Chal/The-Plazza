/*
** EPITECH PROJECT, 2022
** theplazza
** File description:
** Parser
*/

#include "ArgsParser.hpp"

ArgsParser::ArgsParser(int ac, char **av)
{
    _argsNumber = ac;
    _args = av;
}

void ArgsParser::printUsage()
{
    std::cout << "USAGE : \n\t" << "./plazza <cookingTime> <cooksNumber> <refillTime>" << std::endl;
    std::cout << "\t\tThe cooking time need to be a float between 0 and 100, from 0 to 0.99 it will decrease the cooking time time." << std::endl;
    std::cout << "\t\tThe number of cooks need to be an integer between 1 and 50." << std::endl;
    std::cout << "\t\tThe refill time need to be an integer between 1 and 50" << std::endl << std::endl;
    std::cout << "\tHelp for understanding : " << std::endl;
    std::cout << "\t\tWhen a command is about 5 regina, we are sending 5 packed regina to the IPC where the number of pizzas is replaced by the id of the command" << std::endl;
    std::cout << "\t\tSo when you see : Thread x is cooking a 1 8 0 in the kitchen n°x, 1 is the type, 8 the size and 0 the command id" << std::endl << std::endl;
    std::cout << "\tCommands :" << std::endl;
    std::cout << "\t\tstatus -> give infos about current kitchens, cooks and ingredients states" << std::endl;
}

void ArgsParser::setArgs()
{
    if (_argsNumber == 2 && strcmp(_args[1], "-h") == 0) {
        printUsage();
        exit(0);
    } else if (_argsNumber != 4) {
        throw Exceptions("Too few or too much arguments. (-h)");
    } else {
        parseCookingTime(_args[1]);
        parseCooksNumber(_args[2]);
        parseTime(_args[3]);
        
    }
}

void ArgsParser::parseCookingTime(char *arg)
{
    for (int i = 0; arg[i] != '\0'; i++) {
        if (std::isdigit(arg[i]) == 0 && arg[i] != '.') {
            throw Exceptions("The cooking time need to be an float between 0 and 100.");
        }
    }
    _cookingTime = std::stof(arg);
    if (_cookingTime < 0 || _cookingTime > 100)
        throw Exceptions("The cooking time need to be an float between 0 and 100.");
}

void ArgsParser::parseCooksNumber(char *arg)
{
    for (int i = 0; arg[i] != '\0'; i++) {
        if (std::isdigit(arg[i]) == 0) {
            throw Exceptions("The number of cooks need to be an integer between 0 and 100.");
        }
    }
    _cooksNumber = std::stoi(arg);
    if (_cooksNumber < 1 || _cooksNumber > 50)
        throw Exceptions("The number of cooks need to be an integer between 1 and 50.");
}

void ArgsParser::parseTime(char *arg)
{
    for (int i = 0; arg[i] != '\0'; i++) {
        if (std::isdigit(arg[i]) == 0) {
            throw Exceptions("The time to refill ingredients need to be a value in milliseconds between 1 and 50000.");
        }
    }
    _refillTime = std::stoi(arg);
    if (_refillTime < 1 || _refillTime > 50000)
        throw Exceptions("The time to refill ingredients need to be a value in milliseconds between 1 and 50000.");
}