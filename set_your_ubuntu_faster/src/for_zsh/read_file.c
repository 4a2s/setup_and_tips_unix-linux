#include "../../include/my_zsh.h"

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
