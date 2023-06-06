#include <stdio.h>

void printString(Vector* string, const char* start, const char* end) {
	if(string == NULL) return;
    if (start != NULL) printf("%s", start);
	char* buffer = string->buffer;
    for (int i = 0; i < string->length; i++) putchar(buffer[i]);
    if (end != NULL) printf("%s", end);
}

Vector* stringUntil(Vector* string, const char* character) {
	Vector* newstring = ALLOC(Vector);
	newstring->buffer = string->buffer;
	newstring->element_size = sizeof(char);
	newstring->length = string->length;

	char* buffer = string->buffer;
	for(int i = 0; i < string->length; i++) {
		if(buffer[i] == *character) {
			newstring->length = i + 1;
			return newstring;
		}
	}
	return newstring;
}
void replace(Vector* string, const char* from, const char* to) {
	for(int i = 0; i < string->length; i++) {
		if(string->buffer[i] == *from) {
			string->buffer[i] = *to;
		}
	}
}

Vector* split(Vector* string, const char* delimiter) {
	Vector* substrings = ALLOC(Vector);
	substrings->buffer = NULL;
	substrings->element_size = sizeof(Vector*);
	substrings->length = 0;

	Vector* firststring = stringUntil(string, delimiter);
	if(firststring->buffer+firststring->length!=string->buffer+string->length) {
		firststring->length--;
	}
	append(substrings, &firststring);
	for(int i = 0; i < string->length; i++) {
		if(string->buffer[i] == *delimiter) {
			Vector* cutstring = ALLOC(Vector);
			cutstring->buffer = string->buffer + i + 1;
			cutstring->element_size = sizeof(char);
			cutstring->length = string->length - i - 1;

			Vector* substring = stringUntil(cutstring, delimiter);
			if(substring->buffer+substring->length!=string->buffer+string->length) {
				substring->length--;
			}
			append(substrings, &substring);
			free(cutstring);
		}
	}
	return substrings;
}
void pluck(Vector* string) {
	string->buffer++;
	string->length--;
}
void unpluck(Vector* string) {
	string->buffer--;
	string->length++;
}
