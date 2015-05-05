#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <sys/fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <linux/limits.h>
#include "common.h"

void
close_all_fd(void)
{
    close(0);
    close(1);
    close(2);
}

void
copy_files(const char *src, const char *dst)
{
    int pid;

    debug("src: %s\n", src);
    debug("dst: %s\n", dst);

    pid = fork();

    if (pid == 0) {
#ifndef DEBUG
        close_all_fd();
#endif
        execl("/bin/cp", "cp", "-rf", src, dst, NULL);
        exit(0);
    } else {
        wait(NULL);
    }
}

char *
gen_random_string(char *buf, unsigned int size)
{
    int fd;
    char charset[] = { "0123456789abcdef" };

    fd = open("/dev/urandom", O_RDONLY);

    if (fd < 0)
        return buf;

    while(size--) {
        unsigned char byte = 0;

        read(fd, &byte, sizeof(byte));
        *buf++ = charset[byte%(sizeof(charset)-1)];
    }

    *buf = '\0';
    close(fd);
    return buf;
}
