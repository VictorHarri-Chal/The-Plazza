/*
** EPITECH PROJECT, 2021
** B-CCP-400-NAN-4-1-theplazza-victor.harri-chal
** File description:
** Reception.cpp
*/

#include <iostream>
#include <string>
#include <sys/wait.h>
#include <unistd.h>
#include "Exceptions/Exceptions.hpp"
#include "Reception.hpp"
#include "MessageQueue/MessageQueue.hpp"
#include "Log/Log.hpp"
#include "Globals.hpp"
#include <signal.h>
#include <sys/shm.h>

Reception::Reception(float cookingTime, int cooksNumber, int refillTime): _cookingTime(cookingTime), 
_cooksNumber(cooksNumber), _refillTime(refillTime)
{
    _num_cmd = 0;
    _nb_kitchens = 0;
    _id_kitchens = 0;
}

void Reception::shellLoop()
{
    PromptParser promptParser;
    std::string input;
    queue.keyGeneratorRtoK("/tmp", 65);
    queue.emptyQueue(RtoK);
    queue.keyGeneratorKtoR("/bin", 65);
    queue.emptyQueue(KtoR);
    initMutex();
    int ShmId = shmget(IPC_PRIVATE,  sizeof(int), IPC_CREAT | 0666);
    ShmPtr = (int *)shmat(ShmId, NULL, 0);
    ShmPtr[0] = 0;

    std::thread mainThread(&manageReturnQueue);
    while (true) {
        if (!std::getline(std::cin, input)) {
            queue.sendMessageToQueue("close", 1, KtoR);
            deleteMutex();
            queue.destroyQueue(RtoK);
            queue.destroyQueue(KtoR);
            exit(0);
        }
        if (input.empty())
            continue;
        else if (input == "status" && (ShmPtr[0] == 0))
            statusCommand();
        else {
            try {
                newCommand(promptParser, input);
                _num_cmd++;
            } catch (Exceptions &message) {
                message.dispErrorMessage();

            }
        }
    }
}

void Reception::statusCommand()
{
    if (kitchens.size() == 0) {
        std::cout << "No kitchens currently existing." << std::endl;
    }
    ShmPtr[0] = kitchens.size();
}

void Reception::newCommand(PromptParser promptParser, std::string input)
{
    promptParser.checkLoopParsing(input, _num_cmd);
    logger.newLog(input, _num_cmd, false);

    checkIfKitchensNeeded();
}

void Reception::checkIfKitchensNeeded()
{
    if (getNumberOfPlace() < 0) {
        createKitchen();
        checkIfKitchensNeeded();
    }
}

void Reception::createKitchen()
{
    Kitchens kitchen(_id_kitchens, _cookingTime, _cooksNumber, _refillTime);
    kitchens.push_back(kitchen);
    _id_kitchens++;
    pid_t pid = fork();
    if (pid == 0) {
        kitchen.launchKitchen();
        int kitchen_id = kitchen.runKitchen();
        std::string kill_msg = "kill " + std::to_string(kitchen_id);
        kitchen.joinThread();
        kitchen.deleteThreads();
        queue.sendMessageToQueue(kill_msg, 1, KtoR);
        while (true) {}
    }
}

int Reception::getNumberOfPlace()
{
    if (kitchens.size() == 0) {
        return -1;
    }
    int count = (kitchens.size() * (_cooksNumber * 2)) - curr_pizzas;
    return count;
}

void Reception::manageReturnQueue()
{
    while (true) {
        if (queue.countMessagesInQueue(KtoR) != 0) {
            std::string rcv = queue.receiveMessageFromQueue(0, KtoR);
            std::stringstream buffer(rcv);
            std::vector<std::string> parameters;
            std::string parameter;
            while (std::getline(buffer, parameter, ' '))
                parameters.push_back(parameter);
            if (parameters[0] == "close") {
                return;
            }
            if (parameters[0] == "kill") {
                killKitchen(stoi(parameters[1]));
                manageReturnQueue();
            }
            curr_pizzas--;
            pizzas_rcv_per_cmd.at(stoi(parameters[2])) += 1;
            if (pizzas_rcv_per_cmd.at(stoi(parameters[2])) == pizzas_per_cmd.at(stoi(parameters[2]))) {
                logger.newLog(commands.at(stoi(parameters[2])), stoi(parameters[2]), true);
                std::cout << "The order "<< parameters[2] << " is ready : " << commands.at(stoi(parameters[2])) << std::endl;
            }
        }
    }
}

void Reception::killKitchen(int kitchen_id)
{
    std::cout << "Kitchen " << kitchen_id << " has been closed for inactivity." << std::endl;
    kitchens.erase(kitchens.begin() + kitchen_id);
}

void Reception::initMutex()
{
    m1 = new Mutex;
    m2 = new Mutex;
    m3 = new Mutex;
    m4 = new Mutex;
    m5 = new Mutex;
}

void Reception::deleteMutex()
{
    delete m1;
    delete m2;
    delete m3;
    delete m4;
    delete m5;
}
