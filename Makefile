CC=clang
CFLAGS=-Wall -Wextra -O3
ZADANIE=main wolf_handler wolf_draw wolf_helpers wolf_helpers_2 wolf_helpers_3 wolf_loop
OBJ=$(addprefix obj/, $(addsuffix .o, $(ZADANIE)))
LIBFT=libft/libft.a
LIBMLX=libmlx/libmlx.a
NAME=wolf3d

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(LIBMLX)
	@$(CC) -o $(NAME) $(OBJ) $(CFLAGS) -lm -framework AppKit -framework OpenGL libft/libft.a libmlx/libmlx.a
	@echo "Binary is done! 🖥"
$(LIBFT):
	@make -C libft/
	@echo "Library is done! 📚"
$(LIBMLX):
	@make -C libmlx/
	@echo "mlx is done! 👁"
obj/%.o: %.c
	@$(CC) -c $^ -o $@ $(CFLAGS)
clean:
	@rm -f $(OBJ)
	@make -C libft/ clean
	@make -C libmlx/ clean
	@echo "Cleaned the objects! ❌"
fclean: clean
	@rm -f $(NAME)
	@make -C libft/ fclean
	@rm -f libmlx/libmlx.a
	@echo "Cleaned the binary! ☠️"
re: fclean all
	
.PHONY: clean fclean re

