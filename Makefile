NAME = minishell

CC = cc 

FLAGS = -Wall -Wextra -Werror -g -fsanitize=address
READLINE_L = $(shell brew --prefix readline)/lib
READLINE_I = $(shell brew --prefix readline)/include

SRC = ./parsing/ft_strlen.c\
		./parsing/ft_strcmp.c\
		./parsing/ft_strncmp.c\
		./parsing/main.c\
		./parsing/ft_calloc.c\
		./parsing/ft_split.c\
		./parsing/ft_bzero.c\
		./parsing/ft_lst.c\
		./parsing/parssing.c\
		./parsing/parssing0.c\
		./parsing/parssing1.c\
		./parsing/is_empty.c\
		./parsing/freelist.c\
		./parsing/expanding.c\
		./parsing/expanding1.c\
		./parsing/expanding2.c\
		./parsing/here_doc.c\
		./parsing/here_doc1.c\
		./parsing/list_pre.c\
		./parsing/list_pre1.c\
		./parsing/ambiguous.c\
		./parsing/ft_strtrim.c\
		./parsing/util.c\
		./parsing/ft_atoi.c\
		./parsing/env.c\
		./parsing/echo.c\
		./parsing/exit.c\
		./parsing/cd.c\
		./parsing/cd0.c\
		./parsing/mallocerr.c\
		./execution/parsing_pipex.c\
		./execution/ft_strjoinn.c\
		./execution/ft_split.c\
		./execution/ft_str.c\
		./execution/utils.c\
		./execution/utils1.c\
		./execution/pwd.c\
		./execution/ft_lstsize_bonus.c\
		./execution/pipex_bonus.c\
		./execution/unset.c\
		./execution/export.c\
		./execution/export_util.c\
		./execution/redirection.c\
		./execution/handler.c\
		./execution/heredoc.c

OBJ = $(SRC:.c=.o)

INCLUDE1 = execution/ex_minishell.h
INCLUDE2 = parsing/pr_minishell.h

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $@ -L $(READLINE_L) -lreadline 

%.o: %.c $(INCLUDE1) $(INCLUDE2)
	$(CC) $(FLAGS) -I $(READLINE_I) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean