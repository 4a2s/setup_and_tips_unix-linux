CFLAGS	=	-Wall -Wextra -Werror -g3 -pedantic # -fantalize=adress
SRC_DIR	=	src
MAKE_ZSH	=	$(SRC_DIR)/zsh.c
MAKE_CODE	=	$(SRC_DIR)/code.c
BIN	=	a.out

zsh:
	$(CC) $(MAKE_ZSH) $(CFLAGS)
	./$(BIN)
	$(MAKE) fclean

code:
	$(CC) $(MAKE_CODE) $(CFLAGS)
	./$(BIN)
	$(RM) packages.microsoft.gpg
	$(MAKE) fclean

fclean:
	$(RM) $(BIN)

.PHONY: all lib clean fclean re
