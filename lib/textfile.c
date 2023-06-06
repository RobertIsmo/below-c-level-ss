#include <sys/stat.h>

Vector* readTextFile(const char* filename) {
	struct stat st;
	if(stat(filename, &st) != 0) ERROR("Failed to get file size.");

	Vector* text = ALLOC(Vector);
	text->buffer = malloc(st.st_size);
	text->element_size = sizeof(char);
	text->length = st.st_size;

	FILE* file = fopen(filename, "rb");
	if(file == NULL) {
		fclose(file);
		freeVector(text);
		ERROR("Failed to open file.");
	}

	size_t read = fread(text->buffer, 1, text->length, file);
	if(read != (size_t)text->length) {
		fclose(file);
		freeVector(text);
		ERROR("Failed to read file.");
	}

	fclose(file);
	return text;
}

Vector* parseFile(Vector* string) {
	Vector* temp = ALLOC(Vector);
	temp->buffer = string->buffer;
	temp->element_size = string->element_size;
	temp->length = string->length;

	Vector* result = ALLOC(Vector);
	result->buffer = NULL;
	result->element_size = sizeof(Document);
	result->length = 0;

	while(temp->length) {
		Vector* title = stringUntil(temp, "\n");
		replace(title, "\n", " ");
		temp->buffer += title->length;
		temp->length -= title->length;
		Vector* content = stringUntil(temp, "\n");
		replace(content, "\n", " ");
		temp->buffer += content->length;
		temp->length -= content->length;

		Document* doc = ALLOC(Document);
		doc->title = title;
		doc->content = content;
		append(result, doc);
	}
	return result;
}

Vector* getTitle(Vector* documents, int index) {
	return ((Document*)documents->buffer)[index].title;
}
Vector* getContent(Vector* documents, int index) {
	return ((Document*)documents->buffer)[index].content;
}