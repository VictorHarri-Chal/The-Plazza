/*
** EPITECH PROJECT, 2021
** B-CCP-400-NAN-4-1-theplazza-victor.harri-chal
** File description:
** Mutex.cpp
*/

#include "Mutex.hpp"
#include <iostream>

void Mutex::lock()
{
    mtx.lock();
    // std::cout  << "Mutex lock" << std::endl;
}

void Mutex::unlock()
{
    // std::cout  << "Mutex unlock" << std::endl;
    mtx.unlock();
}

void Mutex::trylock()
{
    mtx.try_lock();
}