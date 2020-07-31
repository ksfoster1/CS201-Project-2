//node.h
#pragma once
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include "BST.h"

typedef struct node
{
	BSTNode *b; //value object
	struct node *next;
} Node;

extern Node *newEmptyNode(void);
extern Node *newNode(BSTNode *, Node *);
