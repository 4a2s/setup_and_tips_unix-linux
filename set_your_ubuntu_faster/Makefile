CFLAGS	=	-Wall -Wextra -Werror -g3 -pedantic -MD # -fantalize=adress
SRC_DIR	=	src
DEP_DIR	=	dep
OBJ_DIR	=	obj
SRC	=	$(SRC_DIR)/*.c
OBJ	=	$(SRC:%.c=%.o)
BIN	=	set_ubuntu

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(OBJ) -o $(BIN)
	mv $(SRC_DIR)/*.o $(OBJ_DIR)/
	mv $(SRC_DIR)/*.d $(DEP_DIR)/
	./$(BIN)

clean:
	$(RM) $(OBJ_DIR)/*.o
	$(RM) $(DEP_DIR)/*.d

fclean: clean
	$(RM) $(BIN)

re: fclean all

-include $(OBJ:%.o=%.d)

.PHONY: all lib clean fclean re
