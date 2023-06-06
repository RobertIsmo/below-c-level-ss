#ifndef TEXTILE_H
#define TEXTILE_H

typedef struct {
	Vector* title;
	Vector* content;
} Document;

Vector* readTextFile(const char* filename);
Vector* parseFile(Vector* string);
Vector* getTitle(Vector* documents, int index);
Vector* getContent(Vector* documents, int index);

#endif  // TEXTILE_H
