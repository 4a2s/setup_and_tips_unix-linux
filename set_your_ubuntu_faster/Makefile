CFLAGS	=	-Wall -Wextra -Werror -g3 -pedantic -MD # -fantalize=adress
SRC_DIR	=	src
DEP_DIR	=	dep
OBJ_DIR	=	obj
MAKE_ZSH	=	$(SRC_DIR)/zsh.c
BIN	=	set_ubuntu

zsh:
	$(CC) $(MAKE_ZSH) -o $(BIN) $(CFLAGS)
	./$(BIN)
	$(RM) $(BIN)

fclean: clean
	$(RM) $(BIN)

re: fclean all

.PHONY: all lib clean fclean re
