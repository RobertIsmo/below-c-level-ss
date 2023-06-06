#include <stdio.h>
#include <unistd.h>

int main() {
	printf("\033[1;32m-Welcome to the second module!-\033[0m\n\n");
	sleep(PROMPT_WAIT_TIME);

	printf("\033[1;33m Once again we will load the document... \033[0m");
	Vector* text = readTextFile("documents");
	printf("Finished!\n\n");
	sleep(PROMPT_WAIT_TIME);

	printf("\033[1;33m We have the ability to get the link to these articles. Example...\n \033[0m");
	Vector* title = stringUntil(text, "\n");
	Vector* link = linkToArticle(title);
	printString(link, NULL, "\n\n");
	sleep(PROMPT_WAIT_TIME);

	printf("\033[1;32m-Let's move on to the next module.-\033[0m\n");

	freeVector(link);
	freeVector(text);
	return 0;
}