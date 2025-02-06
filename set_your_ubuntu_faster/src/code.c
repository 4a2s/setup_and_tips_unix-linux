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
        perror("Error of execlp or update_upgrade.\n");
        exit(84);
    } else
        wait(NULL);
}

void install_code(void)
{
    pid_t pid = fork();

    if (pid == -1) {
        perror("Error of fork lol.");
        exit(84);
    }
    if (pid == 0) {
        printf("Exec [install_code]:\n\n");
        execlp("./my_bash/install_code", "my_bash/install_code", (char *)NULL); // exec of command
        perror("Error of execlp or install_code.\n");
        exit(84);
    } else {
        wait(NULL);
        printf("code installed.\n");
    }
}

int main(void)
{
    update_upgrade();
    install_code();
    return 0;
}
