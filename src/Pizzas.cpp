/*
** EPITECH PROJECT, 2021
** B-CCP-400-NAN-4-1-theplazza-victor.harri-chal
** File description:
** Pizzas.cpp
*/

#include "Pizzas.hpp"
#include <thread>
#include <iostream>

Pizzas::Pizzas(PizzaType type, PizzaSize size, int pizza_id, int cook_id, int kitchen_id, float bakingMultiplier): _type(type), _size(size)
{
    setTimeToBake(bakingMultiplier);
    std::cout << "Cook " << cook_id << " is cooking a " << type << " " << size << " " << pizza_id << " in the kitchen n° "<< kitchen_id << " for " << int(_timeToBake) << " seconds!" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(int(_timeToBake * 1000)));
}

Pizzas::~Pizzas()
{
}

PizzaType Pizzas::getPizzaType() const
{
    return _type;
}

PizzaSize Pizzas::getPizzaSize() const
{
    return _size;
}

void Pizzas::setTimeToBake(float bakingMultiplier)
{
    switch(_type) {
        case Margarita :
            _timeToBake = (1 * bakingMultiplier);
            break;
        case Regina :
            _timeToBake = (2 * bakingMultiplier);
            break;
        case Americana :
            _timeToBake = (2 * bakingMultiplier);
            break;
        case Fantasia :
            _timeToBake = (4 * bakingMultiplier);
            break;
    }
}