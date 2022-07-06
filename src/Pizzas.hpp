/*
** EPITECH PROJECT, 2021
** B-CCP-400-NAN-4-1-theplazza-victor.harri-chal
** File description:
** IPizza.hpp
*/

#ifndef _IPIZZA_HPP
    #define _IPIZZA_HPP

    enum PizzaType {
        Regina = 1, 
        Margarita = 2,
        Americana = 4,
        Fantasia = 8
    };

    enum PizzaSize {
        S = 1,
        M = 2,
        L = 4,
        XL = 8,
        XXL = 16
    };

    class Pizzas {
        public:
            Pizzas(PizzaType type, PizzaSize size, int pizza_id, int cook_id, int kitchen_id, float bakingMultiplier);
            ~Pizzas();
            PizzaType getPizzaType() const;
            PizzaSize getPizzaSize() const;
            void setTimeToBake(float bakingMultiplier);
            
        private:
            PizzaType _type;
            PizzaSize _size;
            float _timeToBake;
    };


#endif