
#include <assert.h>
#include <string.h>

void test_veccpy() {
    // Create a mock Vector object
    Vector* vec = (Vector*) malloc(sizeof(Vector));
    vec->buffer = strdup("test_string");
    vec->element_size = sizeof(char);
    vec->length = strlen(vec->buffer);

    // Allocate a destination buffer
    char* dest = (char*) malloc((vec->length + 1) * vec->element_size);

    // Copy the vector to the destination buffer
    veccpy(dest, vec);

    // Verify that the content in the destination buffer is the same as in the vector
    assert(memcmp(dest, vec->buffer, vec->length * vec->element_size) == 0);

    // Cleanup
    free(vec->buffer);
    free(vec);
}

void test_append() {
    // Create a mock Vector object
    Vector* vec = (Vector*) malloc(sizeof(Vector));
    vec->buffer = strdup("test_string");
    vec->element_size = sizeof(char);
    vec->length = strlen(vec->buffer);

    // Create a new element
    char* new_element = strdup("a");

    // Append the new element to the vector
    append(vec, new_element);

    // Verify that the new element was appended correctly
    assert(vec->buffer[vec->length - 1] == *new_element);
    assert((unsigned long)vec->length == strlen(vec->buffer));

    // Cleanup
    free(vec->buffer);
    free(vec);
    free(new_element);
}

void test_compareMemory() {
    // Create two identical memory blocks
    char* ptr1 = strdup("test_string");
    char* ptr2 = strdup("test_string");
    size_t num = strlen(ptr1);

    // Create a different memory block
    char* ptr3 = strdup("different_string");

    assert(compareMemory(ptr1, ptr2, num) == 1);
    assert(compareMemory(ptr1, ptr3, num) == 0);

    // Cleanup
    free(ptr1);
    free(ptr2);
    free(ptr3);
}
void test_isMemoryContained() {
    // Create a container memory block
    char* container = "this is the container string";
    size_t containerSize = strlen(container);

    // Create a memory block that is a subset of the container
    char* memory = "container";
    size_t memorySize = strlen(memory);

    // Create a memory block that is not a subset of the container
    char* memory2 = "not a subset";
    size_t memorySize2 = strlen(memory2);

    // Verify that isMemoryContained() correctly identifies that memory is contained within the container
    assert(isMemoryContained(container, containerSize, memory, memorySize) == 1);

    // Verify that isMemoryContained() correctly identifies that memory2 is not contained within the container
    assert(isMemoryContained(container, containerSize, memory2, memorySize2) == 0);
}

void test_stringUntil() {
    // Create a mock Vector object
    Vector* vec = (Vector*) malloc(sizeof(Vector));
    vec->buffer = strdup("Hello, World!");
    vec->element_size = sizeof(char);
    vec->length = strlen(vec->buffer);

    // Call stringUntil() to create a new vector until a comma
    const char* character = ",";
    Vector* new_vec = stringUntil(vec, character);

    // Verify that the new vector was created correctly
    int new_length = strchr(vec->buffer, *character) - vec->buffer + 1;
    assert(new_vec->length == new_length);
    assert(memcmp(new_vec->buffer, vec->buffer, new_length) == 0);

    // Cleanup
    free(vec->buffer);
    free(vec);
}

void test_replace() {
    // Create a mock Vector object
    Vector* vec = (Vector*) malloc(sizeof(Vector));
    vec->buffer = strdup("Hello, World!");
    vec->element_size = sizeof(char);
    vec->length = strlen(vec->buffer);

    // Define the 'from' and 'to' strings
    const char* from = "W";
    const char* to = "U";

    // Call replace() to replace 'from' with 'to' in the vector
    replace(vec, from, to);

    // Verify that the replacement was made correctly
    // The new buffer should be "Hello, Universe!"
    char* expected_buffer = "Hello, Uorld!";
    assert(strcmp(vec->buffer, expected_buffer) == 0);

    // Cleanup
    free(vec->buffer);
    free(vec);
}

void test_parseFile() {
    // Create a mock Vector object representing the file content
    Vector* fileContent = (Vector*) malloc(sizeof(Vector));
    fileContent->buffer = strdup("Title 1\nContent 1\nTitle 2\nContent 2");
    fileContent->element_size = sizeof(char);
    fileContent->length = strlen(fileContent->buffer);

    // Call parseFile() to parse the documents in the file content
    Vector* documents = parseFile(fileContent);

    // Verify that the documents were parsed correctly
    assert(documents->length == 2);  // there should be 2 documents

    // Verify the first document
    Document* doc1 = &((Document*)documents->buffer)[0];
    assert(strcmp(doc1->title->buffer, "Title 1") == 0);
    assert(strcmp(doc1->content->buffer, "Content 1") == 0);

    // Verify the second document
    Document* doc2 = &((Document*)documents->buffer)[1];
    assert(strcmp(doc2->title->buffer, "Title 2") == 0);
    assert(strcmp(doc2->content->buffer, "Content 2") == 0);

    // Cleanup
    free(fileContent->buffer);
    free(fileContent);

    for (int i = 0; i < documents->length; i++) {
        Document* doc = &((Document*)documents->buffer)[i];
        free(doc->title->buffer);
        free(doc->title);
        free(doc->content->buffer);
        free(doc->content);
    }

    free(documents->buffer);
    free(documents);
}

void test_getTitle() {
    // Create a mock Vector of Documents
    Vector* documents = (Vector*) malloc(sizeof(Vector));
    documents->element_size = sizeof(Document);
    documents->length = 2;

    Document* docs = (Document*) malloc(documents->length * sizeof(Document));
    
    // First Document
    docs[0].title = (Vector*) malloc(sizeof(Vector));
    docs[0].title->buffer = strdup("Title 1");
    docs[0].title->element_size = sizeof(char);
    docs[0].title->length = strlen(docs[0].title->buffer);
    docs[0].content = (Vector*) malloc(sizeof(Vector));
    docs[0].content->buffer = strdup("Content 1");
    docs[0].content->element_size = sizeof(char);
    docs[0].content->length = strlen(docs[0].content->buffer);

    // Second Document
    docs[1].title = (Vector*) malloc(sizeof(Vector));
    docs[1].title->buffer = strdup("Title 2");
    docs[1].title->element_size = sizeof(char);
    docs[1].title->length = strlen(docs[1].title->buffer);
    docs[1].content = (Vector*) malloc(sizeof(Vector));
    docs[1].content->buffer = strdup("Content 2");
    docs[1].content->element_size = sizeof(char);
    docs[1].content->length = strlen(docs[1].content->buffer);

    documents->buffer = (char*) docs;

    // Call getTitle() to retrieve the title of the document at index 1
    Vector* title = getTitle(documents, 1);

    // Verify that the retrieved title is correct
    assert(strcmp(title->buffer, "Title 2") == 0);

    // Cleanup
    free(docs);
    free(documents);
    free(title->buffer);
    free(title);
}

void test_getContent() {
    // Create a mock Vector of Documents
    Vector* documents = (Vector*) malloc(sizeof(Vector));
    documents->element_size = sizeof(Document);
    documents->length = 2;

    Document* docs = (Document*) malloc(documents->length * sizeof(Document));
    
    // First Document
    docs[0].title = (Vector*) malloc(sizeof(Vector));
    docs[0].title->buffer = strdup("Title 1");
    docs[0].title->element_size = sizeof(char);
    docs[0].title->length = strlen(docs[0].title->buffer);
    docs[0].content = (Vector*) malloc(sizeof(Vector));
    docs[0].content->buffer = strdup("Content 1");
    docs[0].content->element_size = sizeof(char);
    docs[0].content->length = strlen(docs[0].content->buffer);

    // Second Document
    docs[1].title = (Vector*) malloc(sizeof(Vector));
    docs[1].title->buffer = strdup("Title 2");
    docs[1].title->element_size = sizeof(char);
    docs[1].title->length = strlen(docs[1].title->buffer);
    docs[1].content = (Vector*) malloc(sizeof(Vector));
    docs[1].content->buffer = strdup("Content 2");
    docs[1].content->element_size = sizeof(char);
    docs[1].content->length = strlen(docs[1].content->buffer);

    documents->buffer = (char*) docs;

    // Call getContent() to retrieve the content of the document at index 1
    Vector* content = getContent(documents, 1);

    // Verify that the retrieved content is correct
    assert(strcmp(content->buffer, "Content 2") == 0);

    // Cleanup
    free(docs);
    free(documents);
    free(content->buffer);
    free(content);
}

void test_split() {
    Vector str = STRING("Hello,World,How,Are,You");
    Vector* substrings = split(&str, ",");
	assert(substrings->length = 5);
    const char* expected[] = {"Hello", "World", "How", "Are", "You"};
    for (int i = 0; i < substrings->length; i++) {
        Vector* substring = ((Vector**)substrings->buffer)[i];
        assert((unsigned long)substring->length == strlen(expected[i]));
        assert(memcmp(substring->buffer, expected[i], substring->length) == 0);
    }

    for (int i = 0; i < substrings->length; i++) {
        free(((Vector*)substrings->buffer)[i].buffer);
    }

    free(substrings->buffer);
    free(substrings);
}


int main() {
	test_veccpy();
	test_append();
	test_compareMemory();
	test_isMemoryContained();
	test_stringUntil();
	test_replace();
	test_getTitle();
	test_getContent();
	test_split();
	return 0;
}