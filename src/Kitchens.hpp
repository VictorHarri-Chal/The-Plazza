/*
** EPITECH PROJECT, 2021
** B-CCP-400-NAN-4-1-theplazza-victor.harri-chal
** File description:
** Kitchens.hpp
*/

#ifndef _KITCHENS_HPP_
    #define _KITCHENS_HPP_

    #include <vector>
    #include <string>
    #include <thread>
    #include "Pizzas.hpp"

    static std::vector<std::string> _orders;
    static std::vector<bool> _cooksState;
    static int _nb_pizzas;
    static bool _shutdown;
    static int _doe;
    static int _tomato;
    static int _gruyere;
    static int _ham;
    static int _mushrooms;
    static int _steak;
    static int _eggplant;
    static int _goat_cheese;
    static int _chief_love;

    class Kitchens {
        public:
            Kitchens(int id, float cookingTime, int cooksNumber, int refillTime);
            ~Kitchens();

            void launchKitchen();
            int runKitchen();
            void statusCmd();
            void takeOrder(int num_orders);
            void restockIngredients();
            void deleteThreads();
            void joinThread();

            static void cook(int id, int kitchen_id, float cookingTime);
            static void cookPizza(std::string pizza, int cook_id, int kitchen_id, float cookingTime);
            static PizzaType identifyType(std::string type);
            static PizzaSize identifySize(std::string size);
            static bool removeIngredients(PizzaType type);
            static void finishedPizzas(int id, std::string pizza);

            inline const int &getId(void) const
            {
                return _id;
            };

            inline const int &getNbPizzas(void) const
            {
                return _nb_pizzas;
            };

            inline const bool &getIfKitchenIsFull(void) const
            {
                return _is_kitchen_full;
            };

            inline const bool &getIfShutdown(void) const
            {
                return _shutdown;
            };

            inline const int &getDoe(void) const
            {
                return _doe;
            };
            
            inline const int &getTomato(void) const
            {
                return _tomato;
            };

            inline const int &getGruyere(void) const
            {
                return _gruyere;
            };

            inline const int &getHam(void) const
            {
                return _ham;
            };

            inline const int &getMushrooms(void) const
            {
                return _mushrooms;
            };
            
            inline const int &getSteak(void) const
            {
                return _steak;
            };

            inline const int &getEggplant(void) const
            {
                return _eggplant;
            };

            inline const int &getGoatCheese(void) const
            {
                return _goat_cheese;
            };

            inline const int &getChiefLove(void) const
            {
                return _chief_love;
            };

        private:
            bool _is_kitchen_full;
            std::vector<std::thread*> _cooks;

            int _id;
            float _cookingTime;
            int _cooksNumber;
            int _refillTime;
    };

#endif
