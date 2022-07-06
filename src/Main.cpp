/*
** EPITECH PROJECT, 2022
** theplazza
** File description:
** Main
*/

#include "Parsers/ArgsParser.hpp"
#include "MessageQueue/MessageQueue.hpp"

int main(int ac, char **av)
{
    try {
        ArgsParser argsParser(ac, av);
        argsParser.setArgs();
        Reception reception(argsParser.getCookingTime(), 
        argsParser.getCooksNumber(), argsParser.getRefillTime());
        reception.shellLoop();
    } catch (Exceptions &message) {
        message.dispErrorMessage();
        return 84;
    }
    return 0;
}
