
Vector* linkToArticle(Vector* title) {
	Vector template = STRING(" https://en.wikipedia.org/wiki/");
	
	Vector* result = ALLOC(Vector);
	result->element_size = sizeof(char);
	result->length = 2 * title->length + template.length;
	result->buffer = malloc(result->length);

	replace(title, "_", " ");
	veccpy(result->buffer, title);
	veccpy(result->buffer + title->length, &template);
	replace(title, " ", "_");
	veccpy(result->buffer + title->length + template.length, title);
	replace(title, "_", " ");
	return result;
}