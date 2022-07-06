/*
** EPITECH PROJECT, 2021
** B-CCP-400-NAN-4-1-theplazza-victor.harri-chal
** File description:
** Mutex.hpp
*/

#ifndef _MUTEX_HPP_
    #define _MUTEX_HPP_

    #include <mutex>

    class Mutex {
        public:
            Mutex() = default;
            ~Mutex() = default;

            void lock();
            void unlock();
            void trylock();
        private:
            std::mutex mtx;
    };

#endif