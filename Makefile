NAME		= cub3D
	
CC			= cc
FLAGS		= -Wall -Wextra -Werror -g3
RM			= rm -rf

OBJDIR = .objFiles

FILES		= main parsing utils display_arg

SRC			= $(FILES:=.c)
OBJ			= $(addprefix $(OBJDIR)/, $(FILES:=.o))
HEADER		= ./libft/libft.h include/cub3d.h include/struct.h
OPTS		= ./libft/libft.a
MLX			= -lX11 -lXext #-L./mlx 


#Colors:
GREEN		=	\e[92;5;118m
YELLOW		=	\e[93;5;226m
GRAY		=	\e[33;2;37m
RESET		=	\e[0m
CURSIVE		=	\e[33;3m


all: $(NAME)

$(NAME): $(OBJ) $(HEADER) | lib

	@printf "$(_SUCCESS) $(GREEN)			-> Compiling $(NAME)...\n$(RESET)"
	@make -C ./libft
	@make -C ./Minilibx
	@$(CC) -IMinilibx $(OBJ) $(OPTS) ./Minilibx/libmlx.a -o $(NAME) $(MLX)
	@printf "$(_SUCCESS) $(GREEN)			-> Finished $(NAME)\n$(RESET)"

$(OBJDIR)/%.o: %.c $(HEADER)
	@mkdir -p $(dir $@)
	@$(CC) $(FLAGS) -c $< -o $@

lib:
	@make -C ./libft

clean:
	@$(RM) $(OBJDIR) $(OBJ)
	@make clean -C ./libft
	@printf "$(YELLOW)			-> Object files removed.$(RESET)\n"

fclean: clean
	@$(RM) $(NAME)
	@make fclean -C ./libft
	@make clean -C ./Minilibx
	@printf "$(YELLOW)			-> Executable removed.$(RESET)\n"

re: fclean all

.PHONY: all clean fclean re bonus lib