BLACK = \033[30m
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
MAGENTA = \033[35m
CYAN = \033[36m
WHITE = \033[37m
RESET = \033[0m

NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror
FFLAGS = #-g3 -fsanitize=thread,undefined#,address

INCLUDES = philo.h
SOURCES = main.c utils.c init.c philo.c super.c
OBJECTS = $(SOURCES:.c=.o)


all : $(NAME)

%.o: %.c $(INCLUDES)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "🔨 $(BLUE)$(notdir $<) $(BLACK)=> $(CYAN)$(notdir $@)$(RESET)"

$(NAME): $(OBJECTS)
	@echo "🔗 $(CYAN)$(notdir $(OBJECTS)) $(BLACK)=> $(YELLOW)$(NAME)$(RESET)"
	@$(CC) $(OBJECTS) $(FFLAGS) -o $(NAME)

clean :
	@echo "🧹 $(BLACK)$(OBJECTS)$(RESET)"
	@rm -rf $(OBJECTS)

fclean : clean
	@echo "🧹 $(BLACK)$(NAME)$(RESET)"
	@rm -f $(NAME)

re : fclean all

run : $(NAME)
	@./$(NAME)

.PHONY : all clean fclean re run
