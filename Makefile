NAME = pipex
CC = gcc
HEADER = pipex.h
CFLAGS = -Wall -Wextra -Werror
SRCS = pipex.c \
		utils.c \
		ft_split.c\
		handle_error.c\

OBJS = $(SRCS:.c=.o)

BGreen=\033[1;32m
BYellow=\033[1;33m
BBlue=\033[1;34m
BPurple=\033[1;38;5;205m
BRed=\033[1;31m
 
all : $(NAME)
	
	@echo " "
	@echo "$(BRed)"
	@echo "██████╗ ██╗██████╗ ███████╗██╗  ██╗"
	@echo "██╔══██╗██║██╔══██╗██╔════╝╚██╗██╔╝"
	@echo "██████╔╝██║██████╔╝█████╗   ╚███╔╝ "
	@echo "██╔═══╝ ██║██╔═══╝ ██╔══╝   ██╔██╗ "
	@echo "██║     ██║██║     ███████╗██╔╝ ██╗ BY y̳i̳s̳m̳a̳i̳l̳i̳"
	@echo "╚═╝     ╚═╝╚═╝     ╚══════╝╚═╝  ╚═╝"

%.o: %.c
	@echo "$(BPurple) Compile $(BYellow) $^ $(BGreen)to $@"
	@$(CC) $(CFLAGS) -c $^ -I $(HEADER) 

$(NAME): $(OBJS)
	@echo "$(BYellow) Make $(BGreen) $@"
	@$(CC) -o $@ $^

clean:
	@echo "$(BBlue) Clean"
	@rm -rf $(OBJS)

fclean: clean
	@echo "$(BGreen) Fclean"
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
