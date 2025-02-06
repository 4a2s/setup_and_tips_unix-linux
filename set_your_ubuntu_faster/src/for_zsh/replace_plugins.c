#include "../../include/my_zsh.h"

static char **set_array_of_passwd(void)
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

static char *parse_the_line(char **full_file, uid_t user_uid, char *user)
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
