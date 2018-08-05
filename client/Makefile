##
## EPITECH PROJECT, 2018
## zappy
## File description:
## makefile client
##

CXX	=	g++ -g3

RM	=	rm -f

SRC	=	src/Main.cpp		\
		src/Socket.cpp		\
		src/ZappyClient.cpp	\
		src/ZappyPlayer.cpp	\
		src/PathFinding.cpp	\
		src/Converter.cpp	\
		src/IncantationInformation.cpp	\
		get_next_line.cpp		\
		get_next_line2.cpp	\


NAME	= zappy_ai

CXXFLAGS	= -I./include -Wall -Wextra -Werror -Wfatal-errors

OBJS	=	$(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(OBJS) -o $(NAME) $(CXXFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY:	all clean fclean re
