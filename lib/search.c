#include <unistd.h>
#include <limits.h>

void quicksort(float* arr, int* indices, int low, int high) {
    if (low < high) {
        int pivotIndex = high;
        float pivot = arr[pivotIndex];
        int i = low - 1;

        for (int j = low; j < high; j++) {
            if (arr[j] >= pivot) {   // Changed here
                i++;
                // Swap arr[i] with arr[j]
                float tempScore = arr[i];
                arr[i] = arr[j];
                arr[j] = tempScore;

                // Swap indices[i] with indices[j]
                int tempIndex = indices[i];
                indices[i] = indices[j];
                indices[j] = tempIndex;
            }
        }

        // Swap arr[i + 1] with arr[high]
        float tempScore = arr[i + 1];
        arr[i + 1] = arr[high];
        arr[high] = tempScore;

        // Swap indices[i + 1] with indices[high]
        int tempIndex = indices[i + 1];
        indices[i + 1] = indices[high];
        indices[high] = tempIndex;

        pivotIndex = i + 1;

        // Recursive calls for the left and right subarrays
        quicksort(arr, indices, low, pivotIndex - 1);
        quicksort(arr, indices, pivotIndex + 1, high);
    }
}

void sortByScores(float* arr, int* indices, int count) {
    quicksort(arr, indices, 0, count - 1);
}



Vector* readString() {
    Vector* string = ALLOC(Vector);
    string->buffer = (char*)malloc(MAX_BUFFER_SIZE);
    string->element_size = sizeof(char);
    string->length = (int)read(STDIN_FILENO, string->buffer, MAX_BUFFER_SIZE - 1);

    // Check for read error immediately
    if (string->length == -1) {
        freeVector(string);
        ERROR("Read string failed.");
    }

    // Null-terminate your string to ensure safety
    string->buffer[string->length] = '\0';

    // Now find the correct length
    int i = 0;
    while (string->buffer[i] != '\0') {
        i++;
    }

    string->length = i-1;
    char* new_buffer = (char*)realloc(string->buffer, string->length);
    // Check for realloc error
    if (new_buffer == NULL) {
        freeVector(string);
        ERROR("Memory reallocation failed.");
    } else {
        string->buffer = new_buffer;
    }

    return string;
}

Results* initializeSearch(Vector* docs) {
    float* scores = (float*)malloc(docs->length * sizeof(float));
    int* indices = (int*)malloc(docs->length * sizeof(int));

    Results* results = ALLOC(Results);
    results->scores = scores;
    results->indices = indices;
    results->count = docs->length;

	for(int i = 0; i < results->count; i++) {
		results->indices[i] = i;
	}

    return results;
}

void SingleTermSearch(Vector* docs, Results* results, Vector* term) {
	for(int i = 0; i < results->count; i++) {
		Vector* content = getContent(docs, i);
		results->scores[i] = isMemoryContained(content->buffer, content->length, term->buffer, term->length);
	}
	sortByScores(results->scores, results->indices, results->count);
}

void MultiTermSearch(Vector* docs, Results* results, Vector* terms) {
	for(int i = 0; i < results->count; i++) {
		Vector* content = getContent(docs, i);
		for(int j = 0; j < terms->length; j++) {
			Vector* term = ((Vector**)terms->buffer)[j];
			results->scores[i] += isMemoryContained(content->buffer, content->length, term->buffer, term->length);
		}
	}
	sortByScores(results->scores, results->indices, results->count);
}
void MultiTermSearchWithOperators (Vector* docs, Results* results, Vector* terms) {
	for(int i = 0; i < results->count; i++) {
		Vector* content = getContent(docs, i);
		int penalty = 0;
		for(int j = 0; j < terms->length; j++) {
			Vector* term = ((Vector**)terms->buffer)[j];
			if(*term->buffer == '+') {
				pluck(term);
				if(isMemoryContained(content->buffer, content->length, term->buffer, term->length) != 1) {
					penalty = INT_MIN;
				} else {
					results->scores[i] += 1;
				}
				unpluck(term);
			} else if(*term->buffer == '-') {
				pluck(term);
				if(isMemoryContained(content->buffer, content->length, term->buffer, term->length) == 1) {
					penalty = INT_MIN;
				} else {
					results->scores[i] += 1;
				}
				unpluck(term);
			} else {
				results->scores[i] += isMemoryContained(content->buffer, content->length, term->buffer, term->length);
			}
		}
		if(penalty < 0) results->scores[i] = 0;
	}
	sortByScores(results->scores, results->indices, results->count);
}
