/*
** EPITECH PROJECT, 2022
** theplazza
** File description:
** Exceptions
*/

#ifndef _EXCEPTIONS_HPP_
    #define _EXCEPTIONS_HPP_

    #include <iostream>
    #include <exception>

    class Exceptions : public std::exception {
        public:
            // Ctor & Dtor
            Exceptions(const std::string &message) noexcept;
            ~Exceptions() = default;

            // Member Functions
            const char *what() const noexcept override ;
            void dispErrorMessage() noexcept;

        protected:
            std::string _message;
    };

#endif