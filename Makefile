NAME := fractol

SRC_PATH := srcs
OBJ_PATH := bin
INC_PATH := includes

SRCS_NAMES =	color_point.c		\
				colors.c			\
				events.c			\
				image.c				\
				interpolate.c		\
				main.c				\
				palette.c			\
				palette_maker.c		\
				palette_parser.c	\
				palette_size.c		\
				window.c			\
				window2.c			\

OBJS_NAMES = $(SRCS_NAMES:.c=.o)

INCS_NAMES =	events.h	\
				fractol.h	\
				image.h		\
				palette.h	\

SRCS = $(addprefix $(SRC_PATH)/, $(SRCS_NAMES))
OBJS = $(addprefix $(OBJ_PATH)/, $(OBJS_NAMES))
INCS = $(addprefix $(INC_PATH)/, $(INCS_NAMES))

LIBFT := libft/libft.a
MLX_PATH := minilibx_macos
MLX = $(MLX_PATH)/libmlx.a
LIBS := -lm -L$(MLX_PATH) -lmlx -Llibft -lft

CC = gcc
CFLAGS = -g -Wall -Werror -Wextra
FRAMEWORKS = -framework OpenGL -framework AppKit
CPPFLAGS = -I$(INC_PATH) -Ilibft/includes -I$(MLX_PATH)
RM = rm -f

NORM_LOG = norm.log
NORM_FILES =

all: $(LIBFT) $(MLX) $(NAME)

$(NAME): $(OBJS) $(INCS)
	@tput dl; tput cub 100; printf "\033[90mCreating object files: \033[32mdone!"
	@printf "\n\033[90mCompiling \033[0m$(NAME)\033[90m: \033[0m"
	@$(CC) -o $(NAME) $(OBJS) $(CFLAGS) $(LIBS) $(FRAMEWORKS)
	@printf "\033[32mdone!\n"

$(LIBFT):
	@make -C libft VERBOSE=0

$(MLX):
	@printf "\033[90mCompiling \033[0m$(MLX)\033[90m: \033[0m"
	@make -C $(MLX_PATH) &> /dev/null
	@printf "\033[32mdone!\n\n"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@tput dl; tput cub 100; printf "\033[90mCreating object files: \033[0m$(notdir $@)"
	@-$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	@$(RM) $(NORM_LOG)
	@$(RM) $(OBJS)
	@$(RM) -r $(NAME).dSYM
	@make -C libft fclean > /dev/null
	@rmdir $(OBJ_PATH) 2> /dev/null || true
	@printf "\033[33mRemoved \033[93mobject files!\033[0m\n"

fclean: clean
	@$(RM) $(NAME)
	@make -C libft fclean &> /dev/null
	@make -C $(MLX_PATH) clean &> /dev/null
	@printf "\033[33mRemoved \033[93m$(NAME) executable!\033[0m\n\n"

re: fclean all

norm:
	@printf "\033[90mChecking \033[0mThe Norm\033[90m...\033[0m\n"
	$(eval NORM_FILES = $(SRCS) $(shell find includes -type f -name "*.h"))
	@printf "Found \033[32m%s\033[0m files!\n" $(words $(NORM_FILES))
	@$(RM) $(NORM_LOG)
	@norminette $(NORM_FILES) >> $(NORM_LOG)
	@printf "Norm Errors: "
	@cat $(NORM_LOG) | grep Error | wc -l | bc
	@printf "See \033[4m$(NORM_LOG)\033[0m for details.\n"

.PHONY: all premsg clean fclean re norm
