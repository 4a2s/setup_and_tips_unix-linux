#include "../../include/my_zsh.h"

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

void free_array_and_file(char **arr, char *file)
{
    for (int i = 0; arr[i] != NULL; i++)
        free(arr[i]);
    free(arr);
    free(file);
}

static void update_upgrade_apt(void)
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

static void install_zsh(void)
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

static void set_up_plugins(void)
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
