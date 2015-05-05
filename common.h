#ifndef CONFIG_H
#define CONFIG_H

//#define DEBUG 1
#undef DEBUG

#ifdef DEBUG
#define debug(...) fprintf(stderr, __VA_ARGS__)
#else
#define debug(...)
#endif

#endif
