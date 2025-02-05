#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

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
    install_zsh();
    set_up_plugins();
    return 0;
}
