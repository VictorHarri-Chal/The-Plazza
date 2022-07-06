/*
** EPITECH PROJECT, 2021
** B-CCP-400-NAN-4-1-theplazza-victor.harri-chal
** File description:
** MessageQueue.cpp
*/

#include "MessageQueue.hpp"

//    HOW TO USE THE QUEUE
// std::string m1("Commande 1"); 
// std::string m2("Commande 2"); 
// MessageQueue queue;

// queue.keyGeneratorRtoK("/tmp", 65);
// queue.keyGeneratorKtoR("/bin", 65);
// std::cout << queue.countMessagesInQueue(RtoK) << std::endl;
// queue.sendMessageToQueue(m1, 1, RtoK);
// std::cout << "Data send is : " << m1 << std::endl;
// std::cout << queue.countMessagesInQueue(RtoK) << std::endl;
// queue.sendMessageToQueue(m2, 1, KtoR);
// std::cout << "Data send is : " << m2 << std::endl;
// std::cout << queue.countMessagesInQueue(KtoR) << std::endl;

// while (true)
// {
//     while (queue.countMessagesInQueue(RtoK) == 0);
//     std::string received = queue.receiveMessageFromQueue(0, RtoK);
//     std::cout << "Data reveived is : " << received << std::endl;
// }

// queue.destroyQueue(RtoK);

void MessageQueue::keyGeneratorRtoK(const std::string &pathname, int proj_id)
{
    key_t key = ftok(pathname.c_str(), proj_id);

    if (key == -1)
        throw Exceptions("ftok error.");

    _RtoK_key = key;
}

void MessageQueue::keyGeneratorKtoR(const std::string &pathname, int proj_id)
{
    key_t key = ftok(pathname.c_str(), proj_id);

    if (key == -1)
        throw Exceptions("ftok error.");
    _KtoR_key = key;
}

void MessageQueue::sendMessageToQueue(const std::string &mesg_text, long mesg_type, Keys queue)
{
    int mesgid = 0;

    if (mesg_text.length() > MAX_MESG_SIZE)
        throw Exceptions("Message to queue too long.");
    if (queue == RtoK)
        mesgid = msgget(_RtoK_key, 0666 | IPC_CREAT);
    else if (queue == KtoR)
        mesgid = msgget(_KtoR_key, 0666 | IPC_CREAT);
    if (mesgid == -1)
        throw Exceptions("msgget error.");
    
    message.mesg_type = mesg_type;
    std::strcpy(message.mesg_text, mesg_text.c_str());
    if (msgsnd(mesgid, &message, sizeof(message), 0) == -1)
        throw Exceptions("msgsnd error.");
}

std::string MessageQueue::receiveMessageFromQueue(long message_type, Keys queue)
{
    int mesgid = 0;

    if (queue == RtoK)
        mesgid = msgget(_RtoK_key, 0666 | IPC_CREAT);
    else if (queue == KtoR)
        mesgid = msgget(_KtoR_key, 0666 | IPC_CREAT);

    if (mesgid == -1)
        throw Exceptions("msgget error.");
    if (msgrcv(mesgid, &message, sizeof(message), message_type, 0) == -1)
            throw Exceptions("msgrcv error.");
    return message.mesg_text;
}

int MessageQueue::countMessagesInQueue(Keys queue)
{
    int mesgid = 0;

    if (queue == RtoK)
        mesgid = msgget(_RtoK_key, 0666 | IPC_CREAT);
    else if (queue == KtoR)
        mesgid = msgget(_KtoR_key, 0666 | IPC_CREAT);

    if (mesgid == -1)
        throw Exceptions("msgget error.");
    struct msqid_ds buf;
    msgctl(mesgid, IPC_STAT, &buf);
    uint count = (uint)(buf.msg_qnum);
    return int(count);
}

void MessageQueue::destroyQueue(Keys queue)
{
    if (queue == RtoK)
        msgctl(_RtoK_key, IPC_RMID, nullptr);
    else if (queue == KtoR)
        msgctl(_KtoR_key, IPC_RMID, nullptr);
}

void MessageQueue::emptyQueue(Keys queue)
{
    for (int i = 0; countMessagesInQueue(queue) != 0; i++) {
        std::string received = receiveMessageFromQueue(0, queue);
    }
}
