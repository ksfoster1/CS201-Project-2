#pragma once
#include "node.h"

typedef struct queue
{
	struct node *front;
	struct node *rear;
	struct node *temp;
	struct node *front1;
	int count;
} Queue;

extern Queue *createQueue(); //creates empty queue
extern void enqueue(Queue *, BSTNode *);
extern BSTNode *dequeue(Queue *);
extern void printQ(Queue *);
