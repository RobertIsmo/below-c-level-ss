#include <stdio.h>
#include <unistd.h>

int main() {
	printf("\033[1;32m-Welcome to the fourth module!-\033[0m\n\n");
	sleep(PROMPT_WAIT_TIME);

	printf("\033[1;33m Once again we will load the document... \033[0m");
	Vector* text = readTextFile("documents");
	printf("Finished!\n\n");
	sleep(PROMPT_WAIT_TIME);
	printf("\033[1;33m Parse the document... \033[0m");
	Vector* docs = parseFile(text);
	printf("Finished!\n\n");
	sleep(PROMPT_WAIT_TIME);

	printf("\033[34m Enter a search query: \033[0m\n");
	Results* results = initializeSearch(docs);
	while(1) {
		Vector* s = readString();
		SingleTermSearch(docs, results, s);
		printf("Top 10 results:\n");
		for(int i = 0; i < 10; i++) {
			printf("score: %f  ", results->scores[i]);
			printString(linkToArticle(getTitle(docs, results->indices[i])), NULL, "\n");
		}
		free(results);
		results = initializeSearch(docs);
		freeVector(s);
	}

	printf("\033[1;32m-Let's move on to the next module.-\033[0m\n");

	freeVector(text);
	return 0;
}