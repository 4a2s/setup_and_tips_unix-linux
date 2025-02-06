#include "../../include/my_zsh.h"

static char **my_while_sep(const char *str, char **words_array, int i, char sep)
{
    int word_len;
    int word_start;

    for (int index = 0; str[i]; index++) {
        while (str[i] && str[i] == sep)
            i++;
        if (str[i] == '\0')
            break;
        word_start = i;
        while (str[i] && str[i] != sep)
            i++;
        word_len = i - word_start;
        words_array[index] = (char *)malloc(sizeof(char) * (word_len + 1));
        if (!words_array[index])
            return NULL;
        for (int j = 0; j < word_len; j++)
            words_array[index][j] = str[word_start + j];
        words_array[index][word_len] = '\0';
    }
    return words_array;
}

static int count_words_sep(const char *str, char sep)
{
    int count = 0;
    int in_word = 0;

    for (int i = 0; str[i]; i++) {
        if (str[i] != sep && !in_word) {
            count++;
            in_word = 1;
            continue;
        }
        if (str[i] == sep)
            in_word = 0;
    }
    return count;
}

char **my_str_to_word_array_custom(const char *my_str, char sep)
{
    int words_count;
    char **words_array;

    if (!my_str)
        return NULL;
    words_count = count_words_sep(my_str, sep);
    words_array = (char **)malloc(sizeof(char *) * (words_count + 1));
    if (!words_array)
        return NULL;
    words_array = my_while_sep(my_str, words_array, 0, sep);
    words_array[words_count] = NULL;
    return words_array;
}
