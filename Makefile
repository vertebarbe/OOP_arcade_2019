##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## Compilation
##

CORE	=	arcade

GAME	=	libgames

all: core games graphicals

core:	$(CORE)

$(CORE):
	make -C ./core

games: $(GAME)

$(GAME):
	make -C ./games/qix
	make -C ./games/solar_fox
	make -C ./games/snake

graphicals:
	make -C ./lib/my_ncurses

clean:
	make clean -C  ./core
	make clean -C ./lib/my_ncurses

fclean:
	make fclean -C  ./core
	make fclean -C ./lib/my_ncurses

re: fclean all

.PHONY: all clean fclean re
