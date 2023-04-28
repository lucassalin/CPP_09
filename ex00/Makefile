NAME		= btc

CC			= c++
CFLAGS		= -Werror -Wextra -Wall -g -std=c++98

INC_PATH	= ./includes/
INC			= -I $(INC_PATH)

SRC_PATH	= ./srcs/
SRC			= $(wildcard $(SRC_PATH)*.cpp)
OBJ_PATH	= ./objects/
OBJ			= $(SRC:$(SRC_PATH)%.cpp=$(OBJ_PATH)%.o)

all: $(OBJ_PATH) $(NAME)

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)

$(OBJ_PATH)%.o: $(SRC_PATH)%.cpp
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(INC)

clean:
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all re clean fclean