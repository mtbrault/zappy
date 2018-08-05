##
## EPITECH PROJECT, 2018
## zappy
## File description:
## makefile
##

all:	zappy_server zappy_gui zappy_ai

zappy_server:
		make -C server/
		mv server/zappy_server .

zappy_ai:
		make -C client/
		mv client/zappy_ai .

zappy_gui:
		make -C gui/
		mv gui/zappy_gui .

clean:
	rm -f zappy_server
	rm -f zappy_ai
	rm -f zappy_gui
	make clean -C server/
	make clean -C client/
	make clean -C gui/

fclean: clean
	make fclean -C server/
	make fclean -C client/
	make fclean -C gui/

re: fclean all

.PHONY: all clean fclean re
