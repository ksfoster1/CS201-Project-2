#include<stdio.h>
#include<stdlib.h>
#include "queue.h"
#include "BST.h"

Queue *createQueue()
{
	Queue *q = (Queue *)malloc(sizeof(Queue));
	q->front = q->rear = NULL;
	q->count = 0;
	return q;
}

void enqueue(Queue *q, BSTNode *b)
{
	Node *n = newNode(b, NULL);

	if (q->front == NULL)
			q->front = q->rear = n;
	else
		{
			q->rear->next = n;
			q->rear = n;
		}

	q->count+=1;
}

BSTNode *dequeue(Queue *q)
{
	BSTNode *tempValue;

	if (q->front == NULL)
	{
		printf("\n Error: Trying to display elements from empty queue");
		return NULL;
	}

	else
	{
			tempValue = q->front->b;
			q->front = q->front->next;
			q->count--;
			return tempValue;
	}
}

void printQ(Queue *q) //this is broken
{
	q->front1 = q->front;
	printf("Queue: ");

	if (q->count == 0)
		printf("Queue Empty!!\n");
	if (q->count == 1)
	{
		printf(q->front1->b->value);
	}

	while (q->front1 != q->rear)
	{
		printf(q->front1->b->value);
		q->front1 = q->front1->next;
	}

	if (q->front1 == q->rear)
		printf(q->front1->b->value);
}