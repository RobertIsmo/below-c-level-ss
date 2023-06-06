#include <stdio.h>
#include <unistd.h>

int main() {
	printf("\033[1;32m-Welcome to the third module!-\033[0m\n\n");
	sleep(PROMPT_WAIT_TIME);

	printf("\033[1;33m Once again we will load the document... \033[0m");
	Vector* text = readTextFile("documents");
	printf("Finished!\n\n");
	sleep(PROMPT_WAIT_TIME);

	printf("\033[1;33m We can get abitrary titles besides the first, and content as well.\n \033[0m");
	sleep(PROMPT_WAIT_TIME);
	printf("\033[34m Parse the documents. \033[0m\n");
	Vector* docs = parseFile(text);
	printf("Finished...\n\n");
	sleep(PROMPT_WAIT_TIME);
	printf("\033[34m Get the third title \033[0m\n");
	printString(getTitle(docs, 2), NULL, "\n");
	sleep(PROMPT_WAIT_TIME);
	printf("\033[34m Get the third content \033[0m\n");
	printString(getContent(docs, 2), NULL, "\n");
	sleep(PROMPT_WAIT_TIME);
	printf("\033[34m Get the 333rd title \033[0m\n");
	printString(getTitle(docs, 332), NULL, "\n");
	sleep(PROMPT_WAIT_TIME);
	printf("\033[34m Get the 589th content \033[0m\n");
	printString(getContent(docs, 588), NULL, "\n");
	sleep(PROMPT_WAIT_TIME);

	printf("\033[1;32m-Let's move on to the next module.-\033[0m\n");

	freeVector(text);
	return 0;
}