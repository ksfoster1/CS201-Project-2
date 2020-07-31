#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include "BST.h"
#include <string.h>
#include "queue.h"

int my_max(int a, int b)
{
	if (a > b)
		return a;
	else
		return b;
}

BST *createBST()
{
	BST *b = malloc(sizeof(BST));
	b->root = NULL;
	return b;
}

BSTNode *insert(BSTNode *root, char *value)
{
	BSTNode *temp;
	temp = (BSTNode *)malloc(sizeof(BSTNode));
	temp->value = value;
	temp->freq = 1;
	temp->left = temp->right = NULL;
	temp->parent = NULL;

	if (root == NULL)
	{
		root = temp;
		root->h = 1;
		return root;
	}
	else
	{
		BSTNode *finalNode = insertHelper(root, temp);
		return finalNode;
	}

}

BSTNode* temp;

BSTNode *insertHelper(BSTNode *current, BSTNode *n)
{	
	if (strcmp(n->value, current->value) < 0)
	{
		if (current->left == NULL)
		{
			current->left = n;
			current->left->parent = current;
			temp = malloc(sizeof(BSTNode));
			temp = current->left;
		}
		else
			insertHelper(current->left, n);
	}

	else if (strcmp(n->value, current->value) > 0)
	{
		if (current->right == NULL)
		{
			current->right = n;
			current->right->parent = current;
			temp = malloc(sizeof(BSTNode));
			temp = current->right;

		}
		else
			insertHelper(current->right, n);
	}

	else if (strcmp(n->value, current->value) == 0) //if already in tree just update tree
	{
		current->freq++;
		temp = malloc(sizeof(BSTNode));
		temp = current;
	}

	return temp;
}

BSTNode *temp;
int isFound;

BSTNode *deleteBST(BSTNode *root, BST *tree, char *key) 
{
	if (root == NULL)
	{
		printf("\nERROR: %s NOT IN TREE", key);
		return root;
	}

	if (isFound == 1)
		isFound = 0;

	if (strcmp(key, root->value) < 0)
		return deleteBST(root->left, tree, key);

	if (strcmp(key, root->value) > 0)
		return deleteBST(root->right, tree, key);

	else 
		{
		if (root->freq > 1) 
		{
			root->freq--;
			return root;
		}

		if (root->left == NULL && root->right != NULL) //1 right child
		{
			temp = (BSTNode *)malloc(sizeof(BSTNode));
			root->right->parent = root->parent;
			isFound = 1;

			if (root->parent == NULL) //if is root
			{
				temp = root;
				root = root->right;
				root->parent = NULL;
				root->right = NULL;
				tree->root = root;
				return temp;
			}

			if (root->parent->left != NULL && root->parent != NULL && strcmp(root->parent->left->value, root->value) == 0) //if left child
			{
				temp = root;
				root->parent->left = root->right;
				return temp;
			}
			else //right child 
			{
				temp = root;
				root->parent->right = root->right;
				return temp;
			}
		}

		else if (root->right == NULL && root->left != NULL) //1 left child 
		{
			temp = (BSTNode *)malloc(sizeof(BSTNode));
			root->left->parent = root->parent;
			isFound = 1;

			if (root->parent == NULL) 
			{
				temp = root;
				root = root->left;
				root->parent = NULL;
				root->left = NULL;
				tree->root = root;
				return temp;
			}
			else if (root->parent->left != NULL && strcmp(root->parent->left->value, root->value) == 0) 
			{
				temp = root;
				root->parent->left = root->left;
				return temp;
			}
			else 
			{
				temp = root;
				root->parent->right = root->left;
				return temp;
			}
		} 
		else if (root->right == NULL && root->left == NULL) //root has no children
		{
			isFound = 1;
			temp = (BSTNode *)malloc(sizeof(BSTNode));
			if (root->parent == NULL) 
			{
				temp = root;
				tree->root = NULL;
				root = NULL;
				return temp;
			}
			if (root->parent->left != NULL && strcmp(root->parent->left->value, root->value) == 0) 
			{
				temp = root;
				root->parent->left = NULL;
				return temp;
			}
			else 
			{
				temp = root;
				root->parent->right = NULL;
				return temp;
			}

		}

		//successor
		else if (root->right != NULL && root->left != NULL && isFound == 0) //node has two children 
		{
			char* v = "";
			temp = (BSTNode *)malloc(sizeof(BSTNode));

			if (root->right != NULL)
				temp = findMin(root->right);
			else
				temp = findMin(root->left);

			v = root->value;
			root->value = temp->value;
			temp->value = v;
			
			return deleteBST(temp, tree, temp->value);
		}
	}
	return temp;
}

BSTNode *deleteAVL(BSTNode *root, BST *tree, char *key)
{
	if (root == NULL)
	{
		printf("\nERROR: %s NOT IN TREE", key);
		return root;
	}

	//find the node
	if (strcmp(key, root->value) < 0)
		return deleteAVL(root->left, tree, key);

	if (strcmp(key, root->value) > 0)
		return deleteAVL(root->right, tree, key);

	else
	{
		if (root->freq > 1)
		{
			root->freq--;
			return root;
		}

		if (root->right == NULL && root->left == NULL) //node has no children
		{
			temp = (BSTNode *)malloc(sizeof(BSTNode));
			if (root->parent == NULL) //i am the root
			{
				temp = root;
				tree->root = NULL;
				root = NULL;
				return temp;
			}
			if (root->parent->left != NULL && strcmp(root->parent->left->value, root->value) == 0)
			{
				temp = root;
				root->parent->left = NULL;
				return temp;
			}
			else
			{
				temp = root;
				root->parent->right = NULL;
				return temp;
			}

		}

		//successor
		else //node has one or two children 
		{
			char* v = "";
			temp = (BSTNode *)malloc(sizeof(BSTNode));

			if (root->right != NULL)
				temp = findMin(root->right);
			else
				temp = findMin(root->left);

			v = root->value;
			root->value = temp->value;
			temp->value = v;

			deleteFixup(temp, tree); //??????
			return deleteAVL(temp, tree, temp->value);
		}
	}
	return temp;
}

BSTNode *find(BSTNode *b, char *value)
{
	if (b == NULL)
	{
		return b;
		printf("TREE IS EMPTY");
	}

	else if (strcmp(b->value, value) > 0)
	{
		return (find(b->left, value));	
	}
		
	else if (strcmp(b->value, value) < 0)
	{
		return (find(b->right, value));
	}

	else if (strcmp(b->value, value) == 0)
	{
		return b;
	}

	else //wha?
	{
		printf("NOT IN TREE");
		return NULL;
	}

}

BSTNode* findMin(BSTNode *node)
{
	BSTNode *temp;
	temp = (BSTNode *)malloc(sizeof(BSTNode));
	temp = node;

	if (node == NULL)
		return NULL;

	if (node->left) 
		return findMin(node->left);

	return temp;
}

void BFS(BSTNode *b, int isAVL)
{
	Queue *q = createQueue();

	BSTNode *traverse;
	traverse = (BSTNode *)malloc(sizeof(BSTNode));

	int level = 0;

	if (b == NULL)
	{
		printf("empty tree");
		return;
	}

	enqueue(q, b); //enqueue the root

	printf("%d: ", level);

	while (q->front != NULL) 
	{
		int levelNodes = q->count;
		while (levelNodes > 0)
		{
			traverse = dequeue(q);
			if (isLeaf(traverse))
				printf("=");
			printf("%s", traverse->value);
			if (isAVL)
				printf("%s", favors(traverse));
			printf("(");
			if (!(traverse->parent)) //if root
				printf("%s", traverse->value);
			else
				printf("%s", traverse->parent->value);
			if (isAVL)
				printf("%s", favors(traverse->parent));
			printf(")");
			printf("%d", traverse->freq);

			if (!(traverse->parent)) //if root
				printf("X");
			else if (traverse->parent->left == traverse)
				printf("L");
			else if (traverse->parent->right == traverse)
				printf("R");

			printf(" ");

			if (traverse->left != NULL)
				enqueue(q, traverse->left);

			if (traverse->right != NULL)
				enqueue(q, traverse->right);

			levelNodes--;
		}

		if (q->front == NULL)
			return;

		printf("\n");
		level++;
		printf("%d: ", level);
	}
}

int isLeaf(BSTNode *b)
{
	if (b == NULL)
		return 0;
	if (b->left == NULL && b->right == NULL)
		return 1;
	else
		return 0;
}

int height(BSTNode *b)
{
	if (b == NULL)
		return 0; //check this
	else  if (b->left == NULL && b->right != NULL)
		return b->right->h + 1;
	else if (b->left != NULL && b->right == NULL)
		return b->left->h + 1;
	else if (b->left == NULL && b->right == NULL)
		return 1;
	else
		return 1 + my_max(b->left->h, b->right->h);
}

int getBalance(BSTNode *b)
{
	int lh = height(b->left);
	int rh = height(b->right);
	int balanceFactor = lh - rh;
	return balanceFactor;
}

int isBalanced(BSTNode *b)
{
	int lh;
	int rh; 

	if (b == NULL)
		return 1;

	lh = height(b->left);
	rh = height(b->right);

	if (abs(lh - rh) <= 1)
		return 1;

	else
		return 0;
}

BSTNode *favorite(BSTNode *b)
{
	if (getBalance(b) >= 1)
		return b->left;
	else if (getBalance(b) <= -1)
		return b->right;
	else //no child is the favorite
		return NULL;
}

char *favors(BSTNode *b)
{
	if (b == NULL)
		return "\0";
	else
	{
		int lh = height(b->left);
		int rh = height(b->right);
		if (lh > rh)
			return "-";
		else if (rh > lh)
			return "+";
		else //favors neither child
			return "\0";
	}
}

void setBalance(BSTNode *b)
{
	b->lh = height(b->left);
	b->rh = height(b->right);
	b->h = height(b);
}

BSTNode *sibling(BSTNode * b)
{
	if (b->parent->left == b && b->parent->right != NULL)
		return b->parent->right;
	if (b->parent->right == b && b->parent->left != NULL)
		return b->parent->left;
	else
		return NULL;
}

int linear(BSTNode *c, BSTNode *p, BSTNode *gp)
{
	return (gp->left == p && p->left == c) || (gp->right == p && p->right == c);
}

void rotate(BSTNode *n, BSTNode *p, BST *tree)
{
	if (p->left == n) //right rotation
	{
		n = p->left;     
		p->left = n->right;                  
		if (n->right != NULL)
			n->right->parent = p;
		n->parent = p->parent;
		if (p->parent == NULL)
			tree->root = n;
		else if (p == p->parent->left)
			p->parent->left = n;
		else
			p->parent->right = n;

		n->right = p;
		p->parent = n;

	}

	if (p->right == n) //left rotation
	{
		n = p->right;
		p->right = n->left;
		if (n->left != NULL)
			n->left->parent = p;
		n->parent = p->parent;
		if (p->parent == NULL)
			tree->root = n;
		else if (p == p->parent->right)
			p->parent->right = n;
		else
			p->parent->left = n;

		n->left = p;
		p->parent = n;
		
	}
}

void insertionFixup(BSTNode *x, BST *tree)
{
	setBalance(x);
	while (x != tree->root)
	{		
		//printf("%s", tree->root);
		if (x->parent != NULL && x->parent->parent == NULL)
			setBalance(x->parent);

		if (favorite(x->parent) == sibling(x))             //case 1
		{
			setBalance(x->parent);
			break; //exit loop
		}
		else if (isBalanced(x->parent))               //case 2
		{
			setBalance(x->parent);
			x = x->parent;
			//continue looping
		}
		else
		{
			BSTNode *y = favorite(x);
			BSTNode *p = x->parent;
			if (y && !(linear(y, x, p))) //case 3
			{
				rotate(y, x, tree);
				rotate(y, p, tree);
				setBalance(x);
				setBalance(p);
				setBalance(y);
			}
			else                                   //case 4
			{
				rotate(x, p, tree);
				setBalance(p);
				setBalance(x);
			}
			break;
		}
	}
}

void deleteFixup(BSTNode *x, BST* tree)
{
	x->h = 0;
	while (x != tree->root)
	{
		if (favorite(x->parent) == x)//case 1
		{
			setBalance(x->parent);
			x = x->parent;
			//continue looping
		}

		else if (favorite(x->parent) == NULL)           //case 2
		{
			setBalance(x->parent);
			break;
		}
		else
		{
			BSTNode *p = x->parent;
			BSTNode *z = sibling(x);
			BSTNode *y = favorite(z);

			if (y && !(linear(y, z, p))) //case 3
			{
				rotate(y, z, tree);
				rotate(y, p, tree);
				setBalance(p);
				setBalance(z);
				setBalance(y);
				x = y;
				//continue looping
			}

			else
			{
				rotate(z, p, tree); //case 4
				setBalance(p);
				setBalance(z);
				if (!(y))
					break;
				x = z;
				//continue looping
			}
		}
	}
}

int getNumberOfNodes(BSTNode *root)
{
	int n;
	if (root == NULL)
		n = 0;
	else
		n = 1 + getNumberOfNodes(root->left) + getNumberOfNodes(root->right);

	return n;
}

int closestNodeWithNullChild(BSTNode *root)
{
	if (getNumberOfNodes(root) == 1)
		return 0;
	else
	{
		Queue *q = createQueue();
		BSTNode *traverse = (BSTNode *)malloc(sizeof(BSTNode));
		int level = 0;
		enqueue(q, root); //enqueue the root

		while (q->front != NULL)
		{
			int levelNodes = q->count;
			while (levelNodes > 0)
			{
				traverse = dequeue(q);

				if (traverse->left == NULL)
					break;

				if (traverse->right == NULL)
					break;

				levelNodes--;
			}

			if (root->left == NULL || root->right == NULL)
				level--;
			level++;
		}

		return level;
	}
}

int furthestNodeWithNullChild(BSTNode *root)
{
	if (getNumberOfNodes(root) == 1)
		return 0;
	else
		return height(root) - 1;
}