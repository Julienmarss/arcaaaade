##
## EPITECH PROJECT, 2025
## Tek 2 B-OOP-400-LIL-4-1-arcade-martin.delebecque
## File description:
## Makefile
##

NAME = arcade_snake.so

SRC = Snake.cpp

OBJ = $(SRC:.cpp=.o)

CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -fPIC -I ../../../includes
LDFLAGS = -shared

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJ) $(LDFLAGS)
	mkdir -p ../../../lib
	cp $(NAME) ../../../lib/$(NAME)
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
	@ echo -e "\033[1;32m$(NAME) successfully created!\033[0m"
	
clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	rm -f ../../../lib/$(NAME)

re: fclean all

.PHONY: all clean fclean re