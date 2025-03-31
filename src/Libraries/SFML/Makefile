##
## EPITECH PROJECT, 2025
## Tek 2 B-OOP-400-LIL-4-1-arcade-martin.delebecque
## File description:
## Makefile
##


NAME = arcade_sfml.so

SRC = SFML.cpp

OBJ = $(SRC:.cpp=.o)

CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -fPIC  -I ../../../includes 
LDFLAGS = -shared

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(LDFLAGS) -o $(NAME) $(OBJ) -lsfml-graphics -lsfml-window -lsfml-system
	cp $(NAME) ../../../lib/$(NAME)
	@ echo -e "\033[1;32m$(NAME) successfully created!\033[0m"
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ 
clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	rm -f ../../../lib/$(NAME)

re: fclean all

.PHONY: all clean fclean re