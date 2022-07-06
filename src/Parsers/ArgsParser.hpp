/*
** EPITECH PROJECT, 2022
** theplazza
** File description:
** ArgsParser
*/

#ifndef PARSER_HPP_
#define PARSER_HPP_

#include <iostream>
#include <cstring>
#include <vector>
#include "../Exceptions/Exceptions.hpp"
#include "../Reception.hpp"

class ArgsParser {
    public:
        ArgsParser(int, char **);
        ~ArgsParser() = default;

        void printUsage();
        void setArgs();
        void parseCookingTime(char *arg);
        void parseCooksNumber(char *arg);
        void parseTime(char *arg);

        inline const float &getCookingTime(void) const
        {
            return _cookingTime;
        };

        inline const int &getCooksNumber(void) const
        {
            return _cooksNumber;
        };

        inline const int &getRefillTime(void) const
        {
            return _refillTime;
        };

    protected:
        char **_args;
        int _argsNumber;

        float _cookingTime;
        int _cooksNumber;
        int _refillTime;
};

#endif /* !PARSER_HPP_ */
