##
## EPITECH PROJECT, 2025
## Tek 2 B-OOP-400-LIL-4-1-tekspice-martin.delebecque
## File description:
## Makefile
##

all: core games graphicals

core:
	$(MAKE) -C src
games:
	$(MAKE) -C src/Games/Snake
graphicals:
	$(MAKE) -C src/Libraries/Ncurses
	$(MAKE) -C src/Libraries/SFML
	$(MAKE) -C src/Libraries/SDL	
clean:
	$(MAKE) -C src clean
	$(MAKE) -C src/Games/Snake clean
	$(MAKE) -C src/Libraries/Ncurses clean
	$(MAKE) -C src/Libraries/SFML clean
	$(MAKE) -C src/Libraries/SDL clean
fclean: clean
	$(MAKE) -C src fclean
	$(MAKE) -C src/Games/Snake fclean
	$(MAKE) -C src/Libraries/Ncurses fclean
	$(MAKE) -C src/Libraries/SFML fclean
	$(MAKE) -C src/Libraries/SDL fclean
	rm -f arcade
	rm -f ./html

re: fclean all
