// Inspired by Zed's dbg.h

#ifndef ERROR_H
#define ERROR_H

#define check(C, ...) if(!(C)) { fprintf(stderr, ##__VA_ARGS__); goto error; }

#endif
