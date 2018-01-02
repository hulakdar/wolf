CC=clang
CFLAGS=-Wall -Wextra -g
ZADANIE=main wolf_handler wolf_draw wolf_helpers wolf_helpers_2 wolf_helpers_3
OBJ=$(addprefix obj/, $(addsuffix .o, $(ZADANIE)))
NAME=wolf3d

all: $(NAME)

$(NAME): $(OBJ) libft/libft.a
	@$(CC) -o $(NAME) $(OBJ) $(CFLAGS) -lm -lmlx -framework OpenGL -framework AppKit libft/libft.a
	@echo "Binary is done! 🖥"
libft/libft.a:
	@make -C libft/
	@echo "Library is done!📚"
obj/%.o: %.c
	@$(CC) -c $^ -o $@ $(CFLAGS)
clean:
	@rm -f $(OBJ)
	@make -C libft/ clean
	@echo "Cleaned the objects! ❌"
fclean: clean
	@rm -f $(NAME)
	@make -C libft/ fclean
	@echo "Cleaned the binary! ☠️"
re: fclean all
	
.PHONY: clean fclean re

