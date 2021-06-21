
NAME			= libvector.a
OUT_PATH		= .

SRCS			= vectors2d.c vectors2f.c vectors2i.c vector_utils.c vec.c

PATH_INC		= vectors.h

BIN_DIR			= bin
OBJS			= $(addprefix $(BIN_DIR)/,$(SRCS:.c=.o))

#GCC
CC				= gcc -c
AR				= ar rcs
RANLIB			= ranlib
OUT				= -o 
CFLAGS			= -Wall -Wextra -Werror
INCLUDES		= -Iincludes -Ilibft

MINFO			= [\033[1;32m$(NAME)\033[0m] : 

all : $(OUT_PATH)/$(NAME)
	@echo "Done."

$(OUT_PATH)/$(NAME) : $(BIN_DIR) $(OBJS)
	@echo "$(MINFO) Linking to lib $@"
	@$(AR) $@ $(OBJS)
	@echo "$(MINFO) Running ranlib."
	@$(RANLIB) $@

$(BIN_DIR)/%.o : %.c $(PATH_INC)
	@echo "$(MINFO) Compiling \033[0;32m$<\033[0m"
	@$(CC) $(OUT) $@ $(CFLAGS) $(INCLUDES) $<

$(BIN_DIR) :
	@echo "$(MINFO) Creating $(BIN_DIR)/ folder."
	@mkdir -p $(BIN_DIR)

clean :
	@echo "$(MINFO) Removing .o"
	@rm -rf $(BIN_DIR)

lclean :
	@echo "$(MINFO) Removing $(LIB_DIR) folder."
	@rm -rf $(LIB_DIR);

fclean : clean lclean
	@rm -rf $(NAME)
	@echo "$(MINFO) Removing $(PATH_OUT)/$(NAME)"

re : fclean all

.PHONY : all clean re fclean clean
