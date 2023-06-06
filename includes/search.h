#ifndef SEARCH_H
#define SEARCH_H

#include "vector.h"

typedef struct {
	float* scores;
	int* indices;
	int count;
} Results;

Vector* readString();
Results* initializeSearch(Vector* docs);

void SingleTermSearch(Vector* docs, Results* results, Vector* term);
void MultiTermSearch(Vector* docs, Results* results, Vector* terms);
void MultiTermSearchWithOperators (Vector* docs, Results* results, Vector* terms);

#endif /* SEARCH_H */
