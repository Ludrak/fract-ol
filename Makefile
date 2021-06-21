
NAME=fract-ol

SRC_DIR=src
BIN_DIR=bin
INC_DIR=inc lib/mlx lib/vector
LIBS=libmlx.a libvector.a
LIB_DIR=lib/

SRCS=main.c color.c utils.c color_palette.c
OBJS=$(addprefix $(BIN_DIR)/,$(SRCS:.c=.o))

FRAMEWORKS=AppKit OpenGL
CFLAGS=-Werror -Wall -Wextra -fsanitize=address -g3 -Ofast -march=native
IFLAGS=$(INC_DIR:%=-I%)
LFLAGS=$(addprefix -L, $(LIBS:lib%.a=$(LIB_DIR)%)) $(LIBS:lib%.a=-l%)
FFLAGS=$(FRAMEWORKS:%=-framework %)

CC=gcc

all: $(NAME)
	@echo Done

$(NAME): $(LIB_DIR)/mlx/libmlx.a $(LIB_DIR)/vector/libvector.a $(BIN_DIR) $(OBJS)
	$(CC) -o $(NAME) $(CFLAGS) $(LFLAGS) $(FFLAGS) $(OBJS)
	@echo "$(NAME): linking done"

$(BIN_DIR)/%.o : $(SRC_DIR)/%.c
	@$(CC) -c -o $@ $(CFLAGS) $(IFLAGS) $<
	@echo "$(NAME): Compiled: $<"

$(BIN_DIR):
	@mkdir -p $(BIN_DIR)
	@echo "$(NAME): created $(BIN_DIR) folder"

$(LIB_DIR)/%.a:
	@make -C $(LIB_DIR)mlx
	@make -C $(LIB_DIR)vector
	

clean:
	@rm -rf $(NAME)

fclean: clean
	@rm -rf $(BIN_DIR)

cleanlib:
	@make -C $(LIB_DIR)/vector fclean
	@make -C $(LIB_DIR)/mlx clean

re: fclean all

.PHONY: all clean fclean re cleanlib
