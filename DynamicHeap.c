/*************************************************************** 
 * Student Name: Jeff Morton
 * File Name: Heap.c
 * Assignment Number: 4
 * Date Due: April 5, 2016
 * 
 *  Created on: Feb 14, 2016
 *      Author: Jeff Morton (jhm14@students.uwf.edu)
 ***************************************************************/

#include "DynamicHeap.h"

#include <stdio.h>
#include <stdlib.h>




typedef struct Node *NodeP;
typedef struct Node
{
	double priority;
	void *info;
} Node;


typedef struct Heap
{
	int size;
	int maxSize;
	Node *array;
} Heap;



void percolateDown(HeapP heap, int slot);
void percolateUp(HeapP heap, Node slot);
void copyNode(HeapP heap, int to, int from);



/**
 * newHeap
 * malloc's a new Heap struct and returns a StructP pointer to it.
 * Remember, this pointer must be type-casted by the program utilizing the ADT
 * @param {int} size - the size of the heap to create
 * @return HeapP pointer to the new Heap
 */
HeapP newHeap( int size )
{
	HeapP heap;
	heap = /*(HeapP)*/malloc(sizeof(Heap));
	if(heap == NULL)	//Checks malloc success.
	{
		fprintf(stderr, "ERROR! Heap Malloc failed!");
		return(heap);
	}
	heap->maxSize = size;
	heap->size = 0;

	heap->array = /*(Node)*/malloc(sizeof(Node)*(size+1));
	if(heap->array == NULL)	//Checks malloc success.
	{
		fprintf(stderr, "ERROR! Array Malloc failed!");
		return(heap);
	}
	return(heap);
}


/**
 * Inserts a new element into the heap with the priority given
 */
void heapInsert(HeapP heap, double priority, void *info)
{
	Node node = heap->array[0];
	node.priority = priority;
	node.info = info;
	//fprintf(stdout, "Node Priority: %lf\n", node.priority);
	percolateUp(heap, node);
	//heap->size++;
	return;
}


/**
 * Extracts an element from the heap with the lowest priority.
 * returns the element as a void pointer
 */
void * heapExtract(HeapP heap)
{
	copyNode(heap, 0, 1);
	copyNode(heap, 1, heap->size);
	heap->size--;
    percolateDown(heap, 1);
    //return(&(heap->array[1]));
    return(heap->array[0].info);
}


void percolateDown(HeapP heap, int slot)
{
	int child;
	NodeP array = heap->array;
	//int tmp = slot; //must know how to compare elements
	Node tmp;
	tmp.info = heap->array[slot].info;
	tmp.priority = heap->array[slot].priority;

	while(slot*2 <= heap->size)
	{
		child = slot*2;
		if(child != heap->size && array[child+1].priority < array[child].priority)
			child++;
		if(array[child].priority < tmp.priority)
			copyNode(heap, slot, child);	//array[slot] = array[child];
		else
			break; //get out of the loop-slot indexes insertion point
		slot = child;
	}
	//array[slot] = tmp;
	//copyNode(heap, slot, tmp);
	array[slot].info = tmp.info;
	array[slot].priority = tmp.priority;
	return;
}


void percolateUp(HeapP heap, Node x) //insert approach
{
	NodeP array = heap->array;
	int slot = ++heap->size;
	while( x.priority < array[slot/2].priority)
	{
		//array[slot] = array[slot/2];
		array[slot].priority = array[slot/2].priority;
		array[slot].info = array[slot/2].info;
		slot /= 2;
	}
	//fprintf(stdout, "%lf\n", x.priority);
	array[slot].info = x.info;
	array[slot].priority = x.priority;
	return;
}


void copyNode(HeapP heap, int to, int from)
{
	heap->array[to].info = heap->array[from].info;
	heap->array[to].priority = heap->array[from].priority;
}


/**
 * returns an element from the heap with the lowest priority.
 */
void * findMin(HeapP heap)
{
	//return(&(heap->array[1]));
	return(heap->array[1].info);
}

/**
 * returns true if the heap is full, otherwise false.
 */
int isFull(HeapP heap)
{
	if(heap->size >= heap->maxSize)
		return(TRUE);
	else
		return(FALSE);
}

/**
 * returns true if empty, otherwise false
 */
int isEmpty(HeapP heap)
{
	if(heap->size <= 0)
		return(TRUE);
	else
		return(FALSE);
}

/**
 * returns the size of the heap
 */
int getSize(HeapP heap)
{
	return(heap->size);
}

/**
 * returns the max size of the heap
 */
int getMaxSize(HeapP heap)
{
	return(heap->maxSize);
}


double getPriority(NodeP node)
{
	return(node->priority);
}


void * getInfo(NodeP node)
{
	return(node->info);
}


void printHeap(HeapP heap)
{
	int i;
	fprintf(stdout, "Heap Size = %d\n", heap->size);
	for(i=1; i<=heap->size; i++)
	{
		fprintf(stdout, "heap[%d]->priority = %lf\n", i, heap->array[i].priority );
	}
	return;
}




