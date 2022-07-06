/*
** EPITECH PROJECT, 2022
** theplazza
** File description:
** PromptParser
*/

#include "../Exceptions/Exceptions.hpp"
#include "PromptParser.hpp"
#include "../Globals.hpp"
#include "../Pizzas.hpp"

void PromptParser::checkLoopParsing(std::string input, int nb_cmd)
{
    bool multipleCommands = false;

    for (int i = 0; input[i]; i++) {
        if (input[i] == ';')
            multipleCommands = true;
    }
    if (multipleCommands)
        checkPizzaCommands(input, nb_cmd);
    else
        checkPizzaCommand(input, nb_cmd);
    commands.push_back(input);
}

void PromptParser::checkPizzaCommands(std::string input, int nb_cmd)
{
    std::stringstream buffer(input);
    std::vector<std::string> commands;
    std::string command;
    
    while (std::getline(buffer, command, ';'))
        commands.push_back(command);
    for (unsigned long i = 0; i < commands.size(); i++) {
        if (commands[i].at(0) == ' ')
            commands[i].erase(commands[i].begin());
        checkPizzaCommand(commands[i], nb_cmd);
    }
}

void PromptParser::checkPizzaCommand(std::string input, int nb_cmd) 
{
    std::stringstream buffer(input);
    std::vector<std::string> parameters;
    std::string parameter;
    
    while (std::getline(buffer, parameter, ' '))
        parameters.push_back(parameter);
    if (parameters.size() != 3)
        throw Exceptions("To order a Pizza here is the requested format \tTYPE SIZE NUMBER [; TYPE SIZE NUMBER]*.");
    checkPizzaType(parameters[0]);
    checkPizzaSize(parameters[1]);
    parameters[2] = checkPizzaNumber(parameters[2]);
    
    if (int(pizzas_per_cmd.size()) != (nb_cmd + 1)) {
        pizzas_per_cmd.push_back(0);
        pizzas_rcv_per_cmd.push_back(0);
    }
    pizzas_per_cmd[nb_cmd] += stoi(parameters[2]);
    std::string command = parameters[0] + " " + parameters[1] + " " + std::to_string(nb_cmd);
    std::string packed_command = pack(command);
    for (int i = 0; i < stoi(parameters[2]); i++) {
        queue.sendMessageToQueue(packed_command, 1, RtoK);
        curr_pizzas++;
    }
}

void PromptParser::checkPizzaType(std::string type)
{
    if (!type.compare("regina"))
        return;
    else if (!type.compare("margarita"))
        return;
    else if (!type.compare("americana"))
        return;
    else if (!type.compare("fantasia"))
        return;
    else
        throw Exceptions("The pizza type needs to be either Regina, Margarita, Americana or Fantasia.");
}

void PromptParser::checkPizzaSize(std::string size)
{
    if (!size.compare("S"))
        return;
    else if (!size.compare("M"))
        return;
    else if (!size.compare("L"))
        return;
    else if (!size.compare("XL"))
        return;
    else if (!size.compare("XXL"))
        return;
    else
        throw Exceptions("The pizza size needs to be either: \tS, M, L XL or XXL.");
}

std::string PromptParser::checkPizzaNumber(std::string size)
{
    if (size.length() > 3)
        throw Exceptions("The pizza number needs to in this format \tx[1..9][0..9]*.");
    if (size[0] != 'x')
        throw Exceptions("The pizza number needs to in this format \tx[1..9][0..9]*.");
    if (size[1] < '1' || size[1] > '9')
        throw Exceptions("The pizza number needs to in this format \tx[1..9][0..9]*.");
    if (size.length() == 3) {
        if (size[2] < '0' || size[2] > '9')
            throw Exceptions("The pizza number needs to in this format \tx[1..9][0..9]*.");
    }
    size.erase(0, 1);
    return size;
}

std::string PromptParser::pack(std::string unpacked_command)
{
    std::stringstream buffer(unpacked_command);
    std::vector<std::string> parameters;
    std::string parameter;
    std::string type;
    std::string size;
    
    while (std::getline(buffer, parameter, ' '))
        parameters.push_back(parameter);
    if (parameters[0].compare("regina") == 0)
        type = "1";
    else if (parameters[0].compare("margarita") == 0)
        type = "2";
    else if (parameters[0].compare("americana") == 0)
        type = "4";
    else if (parameters[0].compare("fantasia") == 0)
        type = "8";
    if (parameters[1].compare("S") == 0)
        size = "1";
    else if (parameters[1].compare("M") == 0)
        size = "2";
    else if (parameters[1].compare("L") == 0)
        size = "4";
    else if (parameters[1].compare("XL") == 0)
        size = "8";
    else if (parameters[1].compare("XXL") == 0)
        size = "16";
    return type + " " + size + " " + parameters[2];
}

std::string PromptParser::unpack(std::string packed_command)
{
    std::stringstream buffer(packed_command);
    std::vector<std::string> parameters;
    std::string parameter;
    std::string type;
    std::string size;
    
    while (std::getline(buffer, parameter, ' '))
        parameters.push_back(parameter);
    if (parameters[0].compare("1") == 0)
        type = "regina";
    else if (parameters[0].compare("2") == 0)
        type = "margarita";
    else if (parameters[0].compare("4") == 0)
        type = "americana";
    else if (parameters[0].compare("8") == 0)
        type = "fantasia";
    if (parameters[1].compare("1") == 0)
        size = "S";
    else if (parameters[1].compare("2") == 0)
        size = "M";
    else if (parameters[1].compare("4") == 0)
        size = "L";
    else if (parameters[1].compare("8") == 0)
        size = "XL";
    else if (parameters[1].compare("16") == 0)
        size = "XLL";
    return type + " " + size + " " + "x" + std::to_string(pizzas_per_cmd.at(stoi(parameters[2])));
}