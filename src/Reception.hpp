/*
** EPITECH PROJECT, 2021
** B-CCP-400-NAN-4-1-theplazza-victor.harri-chal
** File description:
** Reception.hpp
*/

#ifndef _RECEPTION_H_
    #define _RECEPTION_H_

    #include "Parsers/PromptParser.hpp"
    #include "Kitchens.hpp"
    #include <vector>

    static std::vector<Kitchens> kitchens;

    class Reception {
        public:
            Reception(float cookingTime, int _cooksNumber, int _refillTime);
            ~Reception() = default;

            void shellLoop();
            void checkLoopParsing(std::string input);
            void newCommand(PromptParser promptParser, std::string input);
            void createKitchen();
            void checkIfKitchensNeeded();
            int getNumberOfPlace();
            void initMutex();
            void deleteMutex();
            void statusCommand();

            static void manageReturnQueue();
            static void killKitchen(int kitchen_id);

        protected:
            int _num_cmd;
            int _nb_kitchens;
            int _id_kitchens;

            float _cookingTime;
            int _cooksNumber;
            int _refillTime;
    };

#endif
