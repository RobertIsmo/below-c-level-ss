#ifndef FUNC_H
#define FUNC_H

#define ALLOC(type) ((type*)malloc(sizeof(type)))
#define STRING(string_literal) ((Vector){ string_literal, sizeof(char), sizeof(string_literal) - 1 })

#endif /* FUNC_H */