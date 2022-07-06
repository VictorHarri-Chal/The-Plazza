##
## EPITECH PROJECT, 2022
## theplazza
## File description:
## Makefile
##

SRC		=		src/Main.cpp										      \
				src/Exceptions/Exceptions.cpp						\
				src/Parsers/ArgsParser.cpp							\
				src/Parsers/PromptParser.cpp						\
				src/MessageQueue/MessageQueue.cpp				\
				src/Kitchens.cpp									      \
				src/Mutex.cpp										        \
				src/Reception.cpp									      \
				src/Log/Log.cpp 									      \
				src/Globals.cpp 									      \
				src/Pizzas.cpp 											\

OBJ		=	$(SRC:.cpp=.o)

NAME	=	plazza

CC		=	g++

RM 		= 	rm -f

FLAGS   = -Wall -Wextra -Werror -pthread -std=c++20

%.o : %.cpp
	$(CC) -o $@ $(FLAGS) -c $<

all:	$(NAME)

$(NAME):	$(OBJ)
				$(CC) $(FLAGS) -o $(NAME) $(OBJ)
				$(RM) $(OBJ)

clean:
			$(RM)	$(OBJ)

fclean:	clean
			$(RM) 	$(NAME)

re:	fclean all

.PHONY: all clean fclean re
