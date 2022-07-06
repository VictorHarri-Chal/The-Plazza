/*
** EPITECH PROJECT, 2021
** B-CCP-400-NAN-4-1-theplazza-victor.harri-chal
** File description:
** Log.cpp
*/

#include "Log.hpp"

void Log::newLog(const std::string &command, int num_cmd, bool is_finished)
{
    std::time_t time = std::time(0);
    std::tm* curr_time = std::localtime(&time);
    std::fstream file;
    file.open("log-plazza.txt", std::fstream::in | std::fstream::out | std::fstream::app);

    if (!file.is_open()) {
        std::ifstream file("log-plazza.txt");
        file.open("log-plazza.txt", std::fstream::in | std::fstream::out | std::fstream::app);
    }
    fillFile(command, curr_time, file, num_cmd, is_finished);
}

void Log::fillFile(const std::string &command, std::tm* curr_time, std::fstream &file, int num_cmd, bool is_finished)
{
    file << "Command ID : " << num_cmd << " | ";
    curr_time->tm_mday < 10 ? file << "0" << curr_time->tm_mday << "-" : file << curr_time->tm_mday << "-";
    curr_time->tm_mon + 1 < 10 ? file << "0" << curr_time->tm_mon + 1 << "-" : file << curr_time->tm_mon + 1 << "-";
    file << curr_time->tm_year + 1900 << " (";
    curr_time->tm_hour < 10 ? file << "0" << curr_time->tm_hour << ":" : file << curr_time->tm_hour << ":";
    curr_time->tm_min < 10 ? file << "0" << curr_time->tm_min << ":" : file << curr_time->tm_min << ":";
    curr_time->tm_sec < 10 ? file << "0" << curr_time->tm_sec << ") | " : file << curr_time->tm_sec << ") | ";
    file << command;
    if (is_finished)
        file << " READY" << std::endl;
    else
        file << std::endl;
}