#ifndef CONFIG_H
#define CONFIG_H

//#define DEBUG 1
#undef DEBUG

#ifdef DEBUG
#define debug(...) fprintf(stderr, __VA_ARGS__)
#else
#define debug(...)
#endif

void
close_all_fd(void);

void
copy_files(const char *src, const char *dst);

char *
gen_random_string(char *buf, unsigned int size);

#endif
