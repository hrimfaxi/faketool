#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <sys/fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <linux/limits.h>
#include <libgen.h>
#include "common.h"

int
main(int argc, char *argv[])
{
    int i, last;
    char fake_dir[PATH_MAX];
    char *homedir = getenv("HOME");
    char src[PATH_MAX], dst[PATH_MAX], bname[PATH_MAX];
    char randbuf[8+1] = { 0 };

    snprintf(fake_dir, sizeof(fake_dir), "%s/.fake", homedir);
    mkdir(fake_dir, 0755);

    for(i=1; i<argc; ++i) {

        if (argv[i][0] == '-') {
            continue;
        }

        strncpy(src, argv[i], sizeof(src));
        last = strlen(src)-1;
        if (src[last] == '/')
            src[last] = '\0';

        gen_random_string(randbuf, sizeof(randbuf)-1);
        strncpy(bname, src, sizeof(bname));
        snprintf(dst, sizeof(dst), "%s/%s-%ld-%s", fake_dir, basename(bname), time(0), randbuf);
        copy_files(src, dst);
    }

    return execv("/usr/bin/shred", argv);
}
