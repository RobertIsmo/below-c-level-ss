#include <stdio.h>
#include <unistd.h>

int main() {
	printf("\033[1;32m-Hey, Below C Level. Today we are going to do some work on Semantic Search!-\033[0m\n\n");
	sleep(PROMPT_WAIT_TIME);

	printf("\033[1;33m First we need to load our documents file... \033[0m");
	Vector* text = readTextFile("documents");
	printf("Finished!\n\n");
	sleep(PROMPT_WAIT_TIME);

	printf("\033[1;33m Next let's get the first document in the file and print it to the screen... \033[0m\n");
	Vector* title = stringUntil(text, "\n");
	printString(title, NULL, "\n\n");
	sleep(PROMPT_WAIT_TIME);

	printf("\033[1;32m-Let's move on to the next module.-\033[0m\n");

	freeVector(text);
	return 0;
}