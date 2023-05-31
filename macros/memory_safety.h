#ifndef MEMORY_SAFETY_DISABLE_H
#define MEMORY_SAFETY_DISABLE_H

#define gets(...) ((void)0)
#define strcpy(...) ((void)0)
#define strcat(...) ((void)0)
#define sprintf(...) ((void)0)
#define vsprintf(...) ((void)0)
#define scanf(...) ((void)0)
#define fscanf(...) ((void)0)

// Safer alternatives
#define fgets(...) ((void)0)
#define strncpy(...) ((void)0)

#endif /* MEMORY_SAFETY_DISABLE_H */