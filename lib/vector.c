
int compareMemory(char* ptr1, char* ptr2, size_t num) {
    for (size_t i = 0; i < num; ++i) {
        if (ptr1[i] != ptr2[i]) {
			return 0;
		}
    }
    return 1;
}
int isMemoryContained(char* container, size_t containerSize, char* memory, size_t memorySize) {
    if (containerSize < memorySize) {
        return 0;
    }
    for (size_t i = 0; i <= containerSize - memorySize; i++) {
        if (compareMemory(container + i, memory, memorySize) == 1) {
            return 1;
        }
    }
    return 0;
}

void freeVector(Vector* vec) {
	free(vec->buffer);
	free(vec);
}

void veccpy(char* dest, Vector* vec) {
    if (!vec || !dest) {
        return;
    }
    for (unsigned long i = 0; i < vec->length * vec->element_size; i++) {
        dest[i] = vec->buffer[i];
    }
}

void append(Vector* vec, void* element) {
	vec->buffer = realloc(vec->buffer, vec->element_size * (vec->length + 1));
	for(int i = 0; i < (int)vec->element_size; i++) {
		vec->buffer[vec->element_size * vec->length + i] = ((char*)element)[i];
	}
	vec->length++;
}

// Vector* concat(Vector* vec1, Vector* vec2) {

// }