#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <malloc.h>

extern char *clean(char *);
extern char *removeSpace(char *);
extern int ProcessOptions(int, char **);
extern char *isString(FILE *);
extern int main(int, char **);
extern BST *readTree(int, char **);
extern void readCommands(int, BST *, char **);
extern void Fatal(char *fmt, ...);
