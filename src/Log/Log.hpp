/*
** EPITECH PROJECT, 2021
** B-CCP-400-NAN-4-1-theplazza-victor.harri-chal
** File description:
** Log.hpp
*/

#ifndef _LOG_HPP_
    #define _LOG_HPP_

    #include <iostream>
    #include <fstream>
    #include <chrono>

    class Log {
        public:
            Log() = default;
            ~Log() = default;

            void newLog(const std::string &command, int num_cmd, bool is_finished);
            void fillFile(const std::string &command, std::tm* curr_time, std::fstream &file, int num_cmd, bool is_finished);
        private:
    };

#endif