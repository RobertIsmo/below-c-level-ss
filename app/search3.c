#include <stdio.h>
#include <unistd.h>

int main() {
	printf("\033[1;32m-Welcome to the sixth module!-\033[0m\n\n");
	sleep(PROMPT_WAIT_TIME);

	printf("\033[1;33m Let's skip the basic stuff... \033[0m");
	Vector* text = readTextFile("documents");
	Vector* docs = parseFile(text);
	printf("Finished!\n\n");

	printf("\033[34m Enter a search query: \033[0m\n");
	Results* results = initializeSearch(docs);
	while(1) {
		Vector* s = readString();
		Vector* terms = split(s, " ");
		MultiTermSearchWithOperators(docs, results, terms);
		printf("Top 10 results:\n");
		for(int i = 0; i < 10; i++) {
			printf("score: %f  ", results->scores[i]);
			printString(linkToArticle(getTitle(docs, results->indices[i])), NULL, "\n");
		}
		printf("\n");

		free(results);
		results = initializeSearch(docs);
		freeVector(s);
	}

	printf("\033[1;32m-Let's move on to the next module.-\033[0m\n");

	freeVector(text);
	return 0;
}