##
## EPITECH PROJECT, 2025
## Tek 2 B-OOP-400-LIL-4-1-arcade-martin.delebecque
## File description:
## Makefile
##
NAME    = arcade

SRC     = Core/DLLoader.cpp \
		  Core/Application.cpp \
		  Core/MenuManager.cpp \
		  Core/ApplicationError.cpp \
		  Core/Abstract/AGraphicLibrary.cpp \
		  Core/Abstract/AGameLibrary.cpp \
		  Core/Components/RenderComponent.cpp \
		  Core/Components/MenuComponent.cpp \
		  Core/Components/TextComponent.cpp \
		  Core/ToggleLibManager.cpp \
		  Core/ScoreboardManager.cpp \
		  Core/MapManager.cpp \
		  Core/GameManager.cpp \
		  Main.cpp
		

OBJ     = $(SRC:.cpp=.o)

CXX     = g++
CXXFLAGS= -Wall -Wextra -Werror -std=c++20 -fPIC -fno-gnu-unique -I ../includes
LDFLAGS = -ldl

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJ) $(LDFLAGS) 
	cp $(NAME) ../$(NAME)
	@ echo -e "\033[1;32m$(NAME) successfully created!\033[0m"
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
clean:
	rm -f $(OBJ)
	

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
