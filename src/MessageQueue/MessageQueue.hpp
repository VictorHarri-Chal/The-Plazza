/*
** EPITECH PROJECT, 2021
** B-CCP-400-NAN-4-1-theplazza-victor.harri-chal
** File description:
** MessageQueue.hpp
*/

#ifndef _MESSAGE_QUEUE_HPP
    #define _MESSAGE_QUEUE_HPP

    #include <iostream>
    #include <sys/msg.h>
    #include <sys/ipc.h>
    #include <cstring>
    #include "../Exceptions/Exceptions.hpp"

    #define MAX_MESG_SIZE 128

    enum Keys {
        RtoK = 1,
        KtoR = 2
    };

    class MessageQueue {
        public:
            MessageQueue() = default;
            ~MessageQueue() = default;
    
            void keyGeneratorRtoK(const std::string &pathname, int proj_id);
            void keyGeneratorKtoR(const std::string &pathname, int proj_id);
            void sendMessageToQueue(const std::string &mesg_text, long mesg_type, Keys queue);
            std::string receiveMessageFromQueue(long message_type, Keys queue);
            int countMessagesInQueue(Keys queue);
            void destroyQueue(Keys queue);
            void emptyQueue(Keys queue);

            inline const key_t &getRtoKKey(void) const
            {
                return _RtoK_key;
            };

            inline const key_t &getKtoRKey(void) const
            {
                return _KtoR_key;
            };

        private:

            struct mesg_buffer {
                long mesg_type;
                char mesg_text[MAX_MESG_SIZE];
            } message;

            key_t _RtoK_key; // key for the queue from the reception to the kitchens
            key_t _KtoR_key; // key for the queue from the kitchens to the reception
    };

#endif