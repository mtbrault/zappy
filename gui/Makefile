##
## EPITECH PROJECT, 2018
## zappy
## File description:
## gui's makefile
##

CXX	=	g++

RM	=	rm -rf

CPPFLAGS	= -std=c++1z -I./headers/ -I/usr/include/irrlicht

NAME	=	zappy_gui

SRCS	=	src/main.cpp				\
			src/Core.cpp				\
			src/Socket.cpp				\
			src/IrrLib.cpp 				\
			src/MyEventReceiver.cpp 	\
			src/Communication.cpp		\
			src/get_next_line.cpp		\
			src/get_next_line2.cpp		\
			src/ACube.cpp 				\
			src/Actions.cpp 			\
			src/Item.cpp 				\
			src/Music.cpp 				\
			src/Player.cpp 	 			\
			src/Login.cpp 	 			\
			src/MenuItem.cpp			\
			src/Connection.cpp 			\
			src/Render.cpp 				\
			src/Admin.cpp 				\
			src/Guest.cpp 				\
			src/AClient.cpp 			\

OBJS	=	$(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(OBJS) -o $(NAME) $(CPPFLAGS) -lIrrlicht -lpthread -lIrrKlang

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
