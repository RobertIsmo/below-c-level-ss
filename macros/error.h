#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>
#include <stdlib.h>

#define ERROR(message) do { \
    fprintf(stderr, "Error: %s\n", message); \
    exit(1); \
} while (0)

#endif /* ERROR_H */