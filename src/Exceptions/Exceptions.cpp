/*
** EPITECH PROJECT, 2022
** theplazza
** File description:
** Exceptions
*/

#include "Exceptions.hpp"

Exceptions::Exceptions(const std::string &message) noexcept: _message(message) {}

const char *Exceptions::what() const noexcept
{
    return _message.data();
}

void Exceptions::dispErrorMessage() noexcept
{
    std::cerr << "Error: " << _message << std::endl;
}
