#ifndef STRING_H
#define STRING_H

#include "vector.h"

void printString(Vector* string, const char* start, const char* end);
Vector* stringUntil(Vector* string, const char* const character);
void replace(Vector* string, const char* from, const char* to);
Vector* split(Vector* string, const char* delimiter);
void pluck(Vector* string);
void unpluck(Vector* string);
#endif /* STRING_H */
