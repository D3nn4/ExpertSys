NAME = expertSys.exe

SRC =	main.cpp \
			./src/lexer.cpp	\
			./src/rules.cpp	\
			./src/expertSys.cpp

HEADER =	-I./includes

LIB =

all : $(NAME)

$(NAME) :
	g++ -std=c++11 -ggdb3 -Wall -Wextra $(HEADER) -c $(SRC)
	g++ -o $(NAME)   *.o $(LIB)


clean :
	rm -f *.o

fclean : clean
	rm -f $(NAME)

re : fclean all
