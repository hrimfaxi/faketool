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

#ifdef DEBUG
#define debug(...) fprintf(stderr, __VA_ARGS__)
#else
#define debug(...)
#endif

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
    int pid = fork();

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

int
main(int argc, char *argv[])
{
    int i, last;
    char fake_dir[PATH_MAX];
    char *homedir = getenv("HOME");

    snprintf(fake_dir, sizeof(fake_dir), "%s/.fake", homedir);
    mkdir(fake_dir, 0755);

    for(i=1; i<argc; ++i) {
        char src[PATH_MAX], dst[PATH_MAX];
        char randbuf[8] = { 0 };

        if (argv[i][0] == '-') {
            continue;
        }

        strncpy(src, argv[i], sizeof(src));
        last = strlen(src)-1;
        if (src[last] == '/')
            src[last] = '\0';

        gen_random_string(randbuf, 8);
        snprintf(dst, sizeof(dst), "%s/.fake/%s-%ld-%s", homedir, src, time(0), randbuf);
        copy_files(src, dst);
    }
    
    return execv("/bin/shred", argv);
}
