#pragma once
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

typedef struct bstnode
{
	char *value;
	int freq;
	struct bstnode *left;
	struct bstnode *right;
	struct bstnode *parent;
	int h;
	int lh;
	int rh;
} BSTNode;

typedef struct BST
{
	BSTNode *root; 
} BST;

extern int my_max(int, int);
extern BST *createBST();
extern BSTNode *insert(BSTNode *, char *);
extern BSTNode *insertHelper(BSTNode *, BSTNode *);
extern BSTNode *deleteBST(BSTNode *, BST *, char *);
extern BSTNode *deleteAVL(BSTNode *, BST *, char *);
extern BSTNode* find(BSTNode *, char *);
extern BSTNode* findMin(BSTNode *);
extern void BFS(BSTNode *, int);
extern int isLeaf(BSTNode *);
extern int height(BSTNode *);
extern int getBalance(BSTNode *);
extern int isBalanced(BSTNode *);
extern BSTNode *favorite(BSTNode *);
extern char *favors(BSTNode *);
extern void setBalance(BSTNode *);
extern BSTNode *sibling(BSTNode *);
extern int linear(BSTNode *, BSTNode *, BSTNode *);
extern void rotate(BSTNode *, BSTNode *, BST *);
extern void insertionFixup(BSTNode *, BST *);
extern void deleteFixup(BSTNode *, BST*);
extern int getNumberOfNodes(BSTNode *);
extern int closestNodeWithNullChild(BSTNode *);
extern int furthestNodeWithNullChild(BSTNode *);
