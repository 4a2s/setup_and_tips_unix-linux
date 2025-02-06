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

int len_of_array(char **array)
{
    int i = 0;

    for (; array[i]; i++);
    return i;
}

void free_array(char **arr)
{
    for (int i = 0; arr[i] != NULL; i++)
        free(arr[i]);
    free(arr);
}

int my_getnbr(char const *str)
{
    int my_case = 0;
    long res = 0;
    int sign = 1;

    for (; str[my_case] == '-' || str[my_case] == '+'; my_case++)
        if (str[my_case] == '-')
            sign = sign * -1;
    for (; str[my_case] >= '0' && str[my_case] <= '9'; my_case++) {
        res = res * 10 + (str[my_case] - '0');
        if (res * sign > 2147483647 || res * sign < -2147483648)
            return 0;
    }
    return (int)(res * sign);
}


void free_array_and_file(char **arr, char *file)
{
    for (int i = 0; arr[i] != NULL; i++)
        free(arr[i]);
    free(arr);
    free(file);
}

static int verif_bytes(ssize_t total_read,
    size_t buff_size, char *buff, int fd)
{
    char *temp = NULL;

    if (total_read >= (ssize_t)(buff_size)) {
        buff_size *= 2;
        temp = realloc(buff, buff_size);
        if (!temp) {
            free(buff);
            close(fd);
            return 84;
        }
        buff = temp;
    }
    return 0;
}

static ssize_t my_buff(char *buff, int fd, size_t buff_size)
{
    ssize_t bytes_read = 0;
    ssize_t total_read = 0;

    bytes_read = read(fd, buff + total_read, buff_size - total_read - 1);
    while (bytes_read > 0) {
        total_read += bytes_read;
        if (verif_bytes(total_read, buff_size, buff, fd) == 1)
            return 0;
        bytes_read = read(fd, buff + total_read, buff_size - total_read - 1);
    }
    if (bytes_read == -1 || total_read == 0) {
        free(buff);
        close(fd);
        return 0;
    }
    return total_read;
}

static char *fill_buff(int fd, char *buff, size_t buff_size)
{
    ssize_t total_read = 0;

    buff = (char *)malloc(buff_size);
    if (!buff) {
        close(fd);
        return NULL;
    }
    total_read = my_buff(buff, fd, buff_size);
    if (total_read == 0)
        return NULL;
    buff[total_read] = '\0';
    return buff;
}

char *read_status(char *filename, char *buff)
{
    int fd = open(filename, O_RDONLY);
    size_t buff_size = 4096;

    if (fd == -1)
        return NULL;
    buff = fill_buff(fd, buff, buff_size);
    close(fd);
    if (!buff)
        return NULL;
    return buff;
}

int is_sep(char letter, char sep)
{
    return letter != sep;
}

char **my_while_sep(const char *str, char **words_array, int i, char sep)
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

int count_words_sep(const char *str, char sep)
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

char **set_array_of_passwd(void)
{
    char *file = NULL;
    char **full_file;

    file = read_status("/etc/passwd", file);
    if (!file)
        return NULL;
    full_file = my_str_to_word_array_custom(file, '\n');
    free(file);
    return full_file;
}

char *parse_the_line(char **full_file, uid_t user_uid, char *user)
{
    char **parse;

    for (int i = 0; full_file[i]; i++) {
        parse = my_str_to_word_array_custom(full_file[i], ':');
        if (len_of_array(parse) < 3) {
            free_array(parse);
            continue;
        }
        if (my_getnbr(parse[2]) == (int)user_uid) {
            user = strdup(parse[0]);
            break;
        }
        free_array(parse);
    }
    free_array(parse);
    return user;
}

char *get_user_parse(void)
{
    char *user = NULL;
    uid_t user_uid = getuid();
    char **full_file;

    full_file = set_array_of_passwd();
    if (!full_file)
        return NULL;
    user = parse_the_line(full_file, user_uid, user);
    free_array(full_file);
    return user;
}

void update_upgrade_apt(void)
{
    pid_t pid = fork();

    if (pid == -1) {
        perror("Error of fork lol.");
        exit(84);
    }
    if (pid == 0) {
        printf("Exec [update_upgrade]:\n\n");
        execlp("./my_bash/update_upgrade", "my_bash/update_upgrade", (char *)NULL); // exec of command
        perror("Error of execlp or apt but lower chance ;).\n");
        exit(84);
    } else
        wait(NULL);
}

void install_zsh(void)
{
    pid_t pid = fork();

    if (pid == -1) {
        perror("Error of fork lol.");
        exit(84);
    }
    if (pid == 0) {
        printf("Exec [set_up_zsh]:\n\n");
        execlp("./my_bash/set_up_zsh", "my_bash/set_up_zsh", (char *)NULL); // exec of command
        perror("Error of execlp or set_up_zsh.\n");
        exit(84);
    } else {
        wait(NULL);
        printf("ZSH installed.\n");
    }
}

void set_up_plugins(void)
{
    pid_t pid = fork();

    if (pid == -1) {
        perror("Error of fork lol.");
        exit(84);
    }
    if (pid == 0) {
        printf("Exec [set_up_plugins_for_zsh]:\n\n");
        execlp("./my_bash/set_up_plugins_for_zsh", "my_bash/set_up_plugins_for_zsh", (char *)NULL); // exec of command
        perror("Error of execlp or set_up_plugins_for_zsh.\n");
        exit(84);
    } else {
        wait(NULL);
        printf("Plugins installed.\n");
    }
}

void replace_line_in_file(const char *search, const char *replacement, char *user)
{
    FILE *temp_file;
    char line[1024];
    int replaced = 0;
    char *path = (char *)malloc(strlen(user) + 1 + 6 + 7);
    if (!path) {
        fprintf(stderr, "error malloc^^");
        exit(84);
    }
    strcpy(path, "/home/");
    strcat(path, user);
    strcat(path, "/.zshrc");
    printf("path : %s\n", path);
    FILE *file = fopen(path, "r");

    if (file == NULL) {
        free(path);
        perror("Erreur d'ouverture du fichier");
        exit(EXIT_FAILURE);
    }
    temp_file = fopen("temp_file.txt", "w");
    if (temp_file == NULL) {
        perror("Erreur d'ouverture du fichier temporaire");
        fclose(file);
        free(path);
        exit(EXIT_FAILURE);
    }
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, search) && !replaced) {
            fprintf(temp_file, "%s\n", replacement);
            replaced = 1;
        } else
            fputs(line, temp_file);
    }
    fclose(file);
    fclose(temp_file);
    if (remove(path) || rename("temp_file.txt", path)) {
        perror("Erreur lors de la sauvegarde des changements");
        free(path);
        exit(EXIT_FAILURE);
    }
    printf("Modification effectuée avec succès.\n");
    free(path);
}

int main(void)
{
    update_upgrade_apt();
    install_zsh();
    set_up_plugins();
    const char *search = "plugins=(git)";
    const char *replacement = "plugins=(git zsh-syntax-highlighting zsh-autosuggestions zsh-z)";
    char *user = get_user_parse();

    if (!user) {
        fprintf(stderr, "HO NO CRINGE!");
        exit(84);
    }
    replace_line_in_file(search, replacement, user);
    free(user);
    return 0;
}
