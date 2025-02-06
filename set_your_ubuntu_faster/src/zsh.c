#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

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

int main(void)
{
    update_upgrade_apt();
    install_zsh();
    set_up_plugins();
    return 0;
}
