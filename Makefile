RED		= \033[1;31m
GREEN	= \033[1;32m
YELLOW	= \033[1;33m
RESET	= \033[0;37m
SKY		= \033[1;36m

GITHUB = git@github.com:TigranYavroyan/philo.git
GITHUB_FOLDER_NAME = chlp

CC = gcc
SRCSPATH = ./srcs/
INCLPATH = ./includes/
SRCS = $(wildcard $(SRCSPATH)*.c)
OBJS = $(patsubst $(SRCSPATH)%.c, $(SRCSPATH)%.o, $(SRCS))
CFLAGS = $(foreach H, $(INCLPATH), -I$(H)) #-Wall -Wextra -Werror
EXECFLAGS = #-fsanitize=address
NAME = philo

all : $(NAME)

$(NAME) : $(OBJS)
	@$(CC) $(EXECFLAGS) $^ -o $@
	@echo "$(GREEN) Executable file has been created $(RESET)"

$(SRCSPATH)%.o : $(SRCSPATH)%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(YELLOW) Object files have been created $(RESET)"

clean :
	@rm -f $(OBJS)
	@echo "$(RED) Object files have been deleted $(RESET)"

fclean : clean grm
	@rm -f $(NAME)
	@echo "$(RED) Executable file has been deleted $(RESET)"

re : fclean all

grm :
	@rm -rf $(GITHUB_FOLDER_NAME)
	@echo "$(RED) Git repo removed $(RESET)"

copy :
	@cp -r Makefile includes srcs $(GITHUB_FOLDER_NAME)
	@echo "$(SKY) The content copied in git repo $(RESET)"

clone :
	@git clone $(GITHUB) $(GITHUB_FOLDER_NAME)
	@echo "$(SKY) Git repo cloned $(RESET)"

push :
	@git add .
	@git commit -m "something done"
	@git push
	@echo "$(SKY) Pushed $(RESET)"

.PHONY : all clean fclean re push copy clone grm