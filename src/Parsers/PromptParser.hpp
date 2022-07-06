/*
** EPITECH PROJECT, 2022
** theplazza
** File description:
** PromptParser
*/

#ifndef PROMPTPARSER_HPP_
#define PROMPTPARSER_HPP_

#include <iostream>
#include <string>
#include <vector>
#include <sstream>


class PromptParser {
    public:
        PromptParser() = default;
        ~PromptParser() = default;

        void checkLoopParsing(std::string input, int nb_cmd);

        void checkPizzaCommands(std::string input, int nb_cmd);
        void checkPizzaCommand(std::string input, int nb_cmd);

        void checkPizzaType(std::string type);
        void checkPizzaSize(std::string size);
        std::string checkPizzaNumber(std::string number);

        std::string pack(std::string);
        std::string unpack(std::string);

    protected:
};

#endif /* !PROMPTPARSER_HPP_ */
