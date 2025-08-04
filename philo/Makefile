NAME = philo

CC = cc
CFLAGS = -Wall -Werror -Wextra -g

SRCS = src/main.c \
		src/init.c \
		src/utils.c \
		src/routine.c \
		src/parser.c \

OBJS = $(SRCS:.c=.o)

#-----------------------------------------------------------
# Principal
#-----------------------------------------------------------
all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "✅ Proyecto compilado correctamente."

#-----------------------------------------------------------
# Compilar archivos fuente
#-----------------------------------------------------------
%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@  > /dev/null
	@echo "🔧 Compilado: $<"

#-----------------------------------------------------------
# Compilar archivos fuente bonus
#-----------------------------------------------------------
bonus: $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "✅ Proyecto compilado con bonus correctamente."

#-----------------------------------------------------------
# Limpiar archivos fuente
#-----------------------------------------------------------
clean:
	@rm -f $(OBJS)
	@$(MAKE) -C bonus clean > /dev/null
	@echo "🧹 Archivos objeto y temporales eliminados."

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C bonus fclean > /dev/null
	@echo "🧼 Todo limpio."

re: fclean all

.PHONY: all clean fclean re bonus