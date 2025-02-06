#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <termios.h>
#include <crypt.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <shadow.h>

#ifndef MY_ZSH_H_
    #define MY_ZSH_H_

char *read_status(char *filename, char *buff);
void replace_line_in_file(const char *search, const char *replacement, char *user);
void free_array_and_file(char **arr, char *file);
void free_array(char **arr);
int len_of_array(char **array);
char *read_status(char *filename, char *buff);
char **my_str_to_word_array_custom(const char *my_str, char sep);
int my_getnbr(char const *str);
char *get_user_parse(void);

#endif /* !MY_ZSH_H_ */
