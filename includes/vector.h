#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>

typedef struct {
    char* buffer;
	size_t element_size;
    int length;
} Vector;

int compareMemory(char* ptr1, char* ptr2, size_t num);
int isMemoryContained(char* container, size_t containerSize, char* memory, size_t memorySize);
void freeVector(Vector* vec);
void veccpy(char* dest, Vector* vec);
void append(Vector* vec1, void* element);
Vector* concat(Vector* vec1, Vector* vec2);

#endif /* VECTOR_H */
