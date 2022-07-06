/*
** EPITECH PROJECT, 2021
** B-CCP-400-NAN-4-1-theplazza-victor.harri-chal
** File description:
** Kitchens.cpp
*/

#include "Kitchens.hpp"
#include "Globals.hpp"
#include <iostream>
#include <unistd.h>
#include <string>
#include <sstream>

Kitchens::Kitchens(int id, float cookingTime, int cooksNumber, int refillTime): _id(id), _cookingTime(cookingTime), 
_cooksNumber(cooksNumber), _refillTime(refillTime)
{
    std::cout << "Kitchen " << _id << " created" << std::endl;
    _nb_pizzas = 0;
    _is_kitchen_full = false;
    _shutdown = false;
    _doe = 5;
    _tomato = 5;
    _gruyere = 5;
    _ham = 5;
    _mushrooms = 5;
    _steak = 5;
    _eggplant = 5;
    _goat_cheese = 5;
    _chief_love = 5;
}

Kitchens::~Kitchens()
{
}

void Kitchens::launchKitchen()
{
    for (int i = 0; i < _cooksNumber; i++) {
        _cooks.push_back(new std::thread(&cook, i, _id, _cookingTime));
        _cooksState.push_back(true);
    }
}

void Kitchens::joinThread()
{
    for (int i = 0; i < _cooksNumber; i++) {
        _cooks.at(i)->join();
    }
}

int Kitchens::runKitchen()
{

    std::chrono::time_point<std::chrono::system_clock> start, end;
    time_t start1, end1;
    start = std::chrono::system_clock::now();
    start1 = time(nullptr);
    while (true) {
        end1 = time(nullptr);
        if (ShmPtr[0] != 0)
            statusCmd();
        if (!_is_kitchen_full && queue.countMessagesInQueue(RtoK) != 0)
            takeOrder(1);
        if (_nb_pizzas != (_cooksNumber * 2))
            _is_kitchen_full = false;
        if (difftime(end1, start1) == _refillTime) {
            start1 = end1;
            restockIngredients();
        }
        for (size_t i = 0; i < _cooksState.size() - 1; i++) {
            if (_cooksState.at(i) == false)
                start = std::chrono::system_clock::now();
        }
        end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        if (elapsed_seconds.count() > 5) {
            _shutdown = true;
            return _id;
        }
    }
    return 0;
}

void Kitchens::takeOrder(int num_orders)
{
    if (num_orders == 0)
        return;
    for (int i = 0; i < num_orders; i++) {
        m5->lock();
        std::string received = queue.receiveMessageFromQueue(0, RtoK);
        _orders.push_back(received);
        m5->unlock();
        _nb_pizzas++;
        if (_nb_pizzas == (_cooksNumber * 2))
            _is_kitchen_full = true;
    }
}

void Kitchens::statusCmd()
{
    std::cout << "\nKitchen " << _id << " :" << std::endl;
    std::cout << "Doe : " << getDoe() << "\t\t" << "Steak : " << getSteak() << std::endl;
    std::cout << "Tomato : " << getTomato() << "\t" << "Eggplant : " << getEggplant() << std::endl;
    std::cout << "Gruyere : " << getGruyere() << "\t" << "Goat cheese : " << getGoatCheese() << std::endl;
    std::cout << "Ham : " << getHam() << "\t\t" << "Chief love : " << getChiefLove() << std::endl;
    std::cout << "Mushrooms : " << getMushrooms() << std::endl;
    for (size_t i = 0; i < _cooks.size(); i++) {
        if (_cooksState[i])
            std::cout << "Cook " << int(i) << " is not working." << std::endl;
        else if (!_cooksState[i])
            std::cout << "Cook " << int(i) << " is working." << std::endl;
    }
    ShmPtr[0] -= 1;
}

void Kitchens::restockIngredients()
{
    _doe += 1;
    _tomato += 1;
    _gruyere += 1;
    _ham += 1;
    _mushrooms += 1;
    _steak += 1;
    _eggplant += 1;
    _goat_cheese += 1;
    _chief_love += 1;
}

void Kitchens::deleteThreads()
{
    for (int i = 0; i < _cooksNumber ; i++) {
        delete _cooks.at(i);
    }
}

void Kitchens::cook(int id, int kitchen_id, float cookingTime)
{
    while(true) {
        if (_cooksState.at(id) && (_orders.size() != 0)) {
            m1->lock();
            _cooksState.at(id) = false;
            std::string pizza = _orders.at(0);
            _orders.erase(_orders.begin());
            m1->unlock();
            cookPizza(pizza, id, kitchen_id, cookingTime);
            m2->lock();
            finishedPizzas(id, pizza);
            m2->unlock();
        }
        if (_shutdown)
            return;
    }
}

void Kitchens::cookPizza(std::string pizza, int cook_id, int kitchen_id, float cookingTime)
{
    std::stringstream buffer(pizza);
    std::vector<std::string> parameters;
    std::string parameter;
    while (std::getline(buffer, parameter, ' '))
        parameters.push_back(parameter);
    PizzaType type = identifyType(parameters[0]);
    PizzaSize size = identifySize(parameters[1]);
    m3->lock();
    removeIngredients(type);
    m3->unlock();
    m4->lock();
    Pizzas toCook(type, size, stoi(parameters[2]), cook_id, kitchen_id, cookingTime);
    m4->unlock();
}

bool Kitchens::removeIngredients(PizzaType type)
{
    if (type == Margarita) {
        if ((_doe == 0) || (_tomato == 0) || (_gruyere == 0))
            return true;
        else {
            _doe--;
            _tomato--;
            _gruyere--;
        }
    } else if (type == Regina) {
        if ((_doe == 0) || (_tomato == 0) || (_gruyere == 0) || (_ham == 0) || (_mushrooms == 0))
            return true;
        else {
            _doe--;
            _tomato--;
            _gruyere--;
            _ham--;
        }
    } else if (type == Americana) {
        if ((_doe == 0) || (_tomato == 0) || (_gruyere == 0) || (_steak == 0))
            return true;
        else {
            _doe--;
            _tomato--;
            _gruyere--;
            _steak--;
        }
    } else if (type == Fantasia) {
        if ((_doe == 0) || (_tomato == 0) | (_eggplant == 0) || (_goat_cheese == 0) || (_chief_love == 0))
            return true;
        else {
            _doe--;
            _tomato--;
            _eggplant--;
            _goat_cheese--;
            _chief_love--;
        }
    }
    return false;
}

PizzaType Kitchens::identifyType(std::string stype)
{
    PizzaType type;
    if (stoi(stype) == 1)
        type = Margarita;
    else if (stoi(stype) == 2)
        type = Regina;
    else if (stoi(stype) == 4)
        type = Americana;
    else if (stoi(stype) == 8)
        type = Fantasia;
    return type;
}

PizzaSize Kitchens::identifySize(std::string ssize)
{
    PizzaSize size;
    if (stoi(ssize) == 1)
        size = S;
    else if (stoi(ssize) == 2)
        size = M;
    else if (stoi(ssize) == 4)
        size = L;
    else if (stoi(ssize) == 8)
        size = XL;
    else if (stoi(ssize) == 16)
        size = XXL;
    return size;
}

void Kitchens::finishedPizzas(int id, std::string pizza)
{
    _nb_pizzas--;
    _cooksState.at(id) = true;
    queue.sendMessageToQueue(pizza, 1, KtoR);
}