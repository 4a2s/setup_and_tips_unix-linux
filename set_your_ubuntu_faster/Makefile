CFLAGS	=	-Wall -Wextra -g3 -pedantic # -fantalize=adress
SRC_DIR	=	src
SRC_ZSH	=	$(SRC_DIR)/for_zsh/*.c
DIR_BASH	= ./my_bash/
BIN	=	a.out

zsh:
	$(CC) $(SRC_ZSH) $(CFLAGS)
	./$(BIN)
	$(MAKE) fclean

code:
	$(DIR_BASH)update_upgrade
	$(DIR_BASH)install_code
	$(RM) packages.microsoft.gpg

discord:
	$(DIR_BASH)update_upgrade
	$(DIR_BASH)install_discord

fclean:
	$(RM) $(BIN)

.PHONY: all lib clean fclean re
