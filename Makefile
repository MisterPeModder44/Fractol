NAME := fractol

SRC_PATH := srcs
CL_SRC_PATH = $(SRC_PATH)/cl
OBJ_PATH := bin
CL_OBJ_PATH = $(OBJ_PATH)/cl
INC_PATH := includes

SRCS_NAMES =	clamp.c				\
				color_point.c		\
				colors.c			\
				events.c			\
				image.c				\
				init.c				\
				interpolate.c		\
				kargs.c				\
				krun.c				\
				main.c				\
				mandelbrot.c		\
				opencl_utils.c		\
				palette.c			\
				palette_maker.c		\
				palette_parser.c	\
				palette_size.c		\
				quit.c				\
				window.c			\
				window2.c			\

CL_SRCS_NAMES =	mandelbrot.cl

OBJS_NAMES = $(SRCS_NAMES:.c=.o)
CL_OBJS_NAMES = $(CL_SRCS_NAMES:.cl=.clbin)

INCS_NAMES =	clbin.h						\
				events.h					\
				frac_mem.h					\
				fractol.h					\
				ft_opencl.h					\
				ft_opencl_types.h			\
				internal_opencl_types_c.h	\
				internal_opencl_types_cl.h	\
				image.h						\
				palette.h					\

SRCS = $(addprefix $(SRC_PATH)/, $(SRCS_NAMES))
CL_SRCS = $(addprefix $(CL_SRC_PATH)/, $(CL_SRCS_NAMES))
OBJS = $(addprefix $(OBJ_PATH)/, $(OBJS_NAMES))
CL_OBJS = $(addprefix $(CL_OBJ_PATH)/, $(CL_OBJS_NAMES))
INCS = $(addprefix $(INC_PATH)/, $(INCS_NAMES))

LIBFT := libft/libft.a
MLX_PATH := minilibx_macos
MLX = $(MLX_PATH)/libmlx.a
LIBS := -lm -L$(MLX_PATH) -lmlx -Llibft -lft

CC = /usr/bin/gcc
CLC = /System/Library/Frameworks/OpenCL.framework/Libraries/openclc
CFLAGS = -g -Wall -Werror -Wextra -O3
FRAMEWORKS = -framework OpenCL -framework OpenGL -framework AppKit
CPPFLAGS = -I$(INC_PATH) -Ilibft/includes -I$(MLX_PATH)
RM = /bin/rm -f

ifeq ($(DEBUG), 1)
CFLAGS += -D DEBUG=1
endif

NORM_LOG = norm.log
NORM_FILES =

all: $(LIBFT) $(MLX) $(NAME)

$(NAME): $(CL_OBJS) $(OBJS)
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

$(CL_OBJ_PATH)/%.clbin: $(CL_SRC_PATH)/%.cl $(INCS)
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@mkdir $(CL_OBJ_PATH) 2> /dev/null || true
	@tput dl; tput cub 100; printf "\033[90mCreating OpenCL binary files: \033[0m$(notdir $@)\n"
	@$(CLC) -I$(INC_PATH) -cl-std=CL1.2 -emit-llvm -c -arch gpu_64 $< -o $@

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(INCS)
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@tput dl; tput cub 100; printf "\033[90mCreating object files: \033[0m$(notdir $@)"
	@-$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	@$(RM) $(NORM_LOG)
	@$(RM) $(OBJS)
	@$(RM) $(CL_OBJS)
	@$(RM) -r $(NAME).dSYM
	@make -C libft clean > /dev/null
	@rmdir $(CL_OBJ_PATH) 2> /dev/null || true
	@rmdir $(OBJ_PATH) 2> /dev/null || true
	@printf "\033[33mRemoved \033[93mobject files!\033[0m\n"

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(NAME)_debug
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
