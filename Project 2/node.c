//node.c

#include "node.h"
#include "BST.h"

Node *newEmptyNode(void)
{
	Node *p = malloc(sizeof(Node));     
	p->b = NULL;                     
	p->next = NULL;
	//p->left = 0;
	//p->right = 0;
	return p;
}

Node *newNode(BSTNode *b, Node *n)
{
	Node *p = malloc(sizeof(Node));     
	p->b = b;
	p->next = n;
	return p;
}


