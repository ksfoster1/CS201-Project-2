#define _CRT_NONSTDC_NO_WARNINGS //because visual studio
#define _CRT_SECURE_NO_WARNINGS 
#define _CRT_SECURE_NO_WARNINGS_GLOBALS 

#include <stdio.h>
#include <stdarg.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include "scanner.h"
#include "BST.h"
#include "trees.h"
#include <ctype.h>

//* options        *
//* option -a      *  AVL
//* option -b      *  BST

char *isString(FILE *fp)
{
	char *v;
	if (stringPending(fp))
	{
		v = readString(fp);
		//char *h = clean(v);
		//char *r = removeSpace(h);
		return v;
	}
	else
	{
		v = readToken(fp);
		//char *h = clean(v);
		//char *r = removeSpace(h);
		return v;
	}
}

int main(int argc, char **argv)
{
	int argIndex = ProcessOptions(argc, argv);
	if (argIndex)
		return 0;
}

BST *readTree(int isAVL, char **corpus)
{
	BST *tree = createBST();
	FILE *fp = fopen(corpus[2], "r");
	char *v = isString(fp);
	//printf("original word is %s", v);
	v = clean(v);
	v = removeSpace(v);
	//printf("\n cleaned word is %s", v);

	while (v != 0 && v != NULL)
	{
		if (strlen(v) == 0)
		{
			//do not insert empty strings into file
		}
		else
		{
			BSTNode *temp = (BSTNode *)malloc(sizeof(BSTNode));
			if (tree->root == NULL)
				tree->root = insert(tree->root, v);
			else
			{
				temp = insert(tree->root, v);
				if (isAVL)
					insertionFixup(temp, tree);
			}
		}

			v = isString(fp);
			if (v == NULL)
				break;
			v = clean(v);
			v = removeSpace(v);
	}
	return tree;
	fclose(fp);
}

void readCommands(int isAVL, BST *tree, char **commands)
{
	FILE *fp = fopen(commands[3], "r");
	char *v = isString(fp);
	BSTNode *temp = (BSTNode *)malloc(sizeof(BSTNode));

	while (v != 0 && v != NULL)
	{
		if (strcmp(v, "i") == 0)
		{
			v = isString(fp);
			v = clean(v);
			v = removeSpace(v);
			temp = insert(tree->root, v);
			if (tree->root == NULL)
				tree->root = temp;
			if (isAVL)
				insertionFixup(temp, tree);
		}

		else if (strcmp(v, "d") == 0)
		{
			v = isString(fp);
			v = clean(v);
			v = removeSpace(v);
			if (isAVL)
				temp = deleteAVL(tree->root, tree, v);
			else
				temp = deleteBST(tree->root, tree, v);
		}

		else if (strcmp(v, "f") == 0)
		{
			v = isString(fp);
			BSTNode *f = find(tree->root, v);
			if (f != NULL)
			{
				printf("\n");
				printf("VALUE IS %s", f->value);
				printf(" FREQUENCY IS %d", f->freq);
			}
		}

		else if (strcmp(v, "s") == 0)
		{
			printf("\n");
			BFS(tree->root, isAVL);
		}

		else if (strcmp(v, "r") == 0)
		{
			int num = getNumberOfNodes(tree->root);
			if (num == 0)
			{
				printf(" empty tree");
			}
			else
			{
				printf("\nthe number of nodes in the tree: %d", num);
				int num2 = closestNodeWithNullChild(tree->root);
				printf("\nthe distance from the root to the closest node with a null child pointer: %d", num2);
				int num3 = furthestNodeWithNullChild(tree->root);
				printf("\nthe distance from the root to the furthest node with a null child pointer: %d", num3);
			}
		}
		v = isString(fp);
	}
	fclose(fp);
}

char *clean(char *v) 
{
	int i;
	int j;
	char *m = malloc(sizeof(char) * (strlen(v) + 1));
	j = 0;
	for (i = 0; i < strlen(v); ++i) 
	{
		if (isascii((int)(v[i])))
		{
			if (isalpha((int)(v[i])) || isspace((int)(v[i])))
			{
				char c = tolower((int)(v[i]));
				m[j] = c;
				++j;
			}
		}
		else
			continue;
	}
	m[j] = '\0';
	return m;
}
char *removeSpace(char *v) 
{
	int i;
	int j;
	int k = 0;
	char *m = malloc(sizeof(char)*(strlen(v) + 1));
	j = 0;
	for (i = 0; i < strlen(v); ++i) 
	{
		if (isspace((int)(v[i])) && k == 0) 
		{
			m[j] = ' ';
			k = 1;
			++j;
		}
		else if (isspace((int)(v[i])) && k == 1) 
		{
			//do nothing
		}
		else 
		{
			m[j] = v[i];
			k = 0;
			++j;
		}
	}
	m[j] = '\0';
	return m;
} 

int ProcessOptions(int argc, char **argv)
{
	FILE *fp;
	int argIndex;
	int argUsed;
	int separateArg;
	char *arg;

	//if (arg) {};

	argIndex = 1;

	while (argIndex < argc && *argv[argIndex] == '-')
	{
		//* check if stdin, represented by "-" is an argument *
		//* if so, the end of options has been reached *
		if (argv[argIndex][1] == '\0') return argIndex;

		separateArg = 0;
		argUsed = 0;

		int isAVL = 0; //0 if BST or 1 if AVL

		if (argv[argIndex][2] == '\0')
		{
			arg = argv[argIndex + 1];
			separateArg = 1;
		}
		else
			arg = argv[argIndex] + 2;

		switch (argv[argIndex][1])
		{
		case 'a':
			if (argc == 4)
			{
				BST *a = createBST();
				isAVL = 1;
				a = readTree(isAVL, argv);
				readCommands(isAVL, a, argv);
			}
			else
				printf("ERROR");
			argUsed = 1;
			exit(0);
		case 'b':
			if (argc == 4)
			{
				BST *b = createBST();
				isAVL = 0;
				b = readTree(isAVL, argv);
				readCommands(isAVL, b, argv);
			}
			else
				printf("ERROR");
			argUsed = 1;
			exit(0);
		default:
			Fatal("option %s not understood\n", argv[argIndex]);
		}
		if (separateArg && argUsed)
			++argIndex;
		++argIndex;
	}
	return argIndex;
	fclose(fp);
}

void Fatal(char *fmt, ...)
{
	va_list ap;

	fprintf(stderr, "An error occured: ");
	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	va_end(ap);

	exit(-1);
}

