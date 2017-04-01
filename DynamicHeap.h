/*************************************************************** 
 * Student Name: Jeff Morton
 * File Name: Heap.h
 * Assignment Number: 4
 * Date Due: April 5, 2016
 * 
 *  Created on: Feb 14, 2016
 *      Author: Jeff Morton (jhm14@students.uwf.edu)
 ***************************************************************/

#ifndef DYNAMICHEAP_H_
#define DYNAMICHEAP_H_



#define TRUE 1
#define FALSE 0

//typedef struct Node *NodeP; //no longer usabe by the user.

typedef struct Heap *HeapP;

/**
 * newHeap
 * malloc's a new Heap struct and returns a StructP pointer to it.
 * Remember, this pointer must be type-casted by the program utilizing the ADT
 * @param {int} size - the size of the heap to create
 * @return HeapP pointer to the new Heap
 */
HeapP newHeap( int size );

/**
 * Inserts a new element into the heap with the priority given
 */
void heapInsert(HeapP heap, double priority, void *info);

/**
 * Extracts an element from the heap with the lowest priority.
 * returns the element as a void pointer
 */
void * heapExtract(HeapP heap);

/**
 * returns an element from the heap with the lowest priority.
 */
void * findMin(HeapP heap);

/**
 * returns true if the heap is full, otherwise false.
 */
int isFull(HeapP heap);

/**
 * returns true if empty, otherwise false
 */
int isEmpty(HeapP heap);

/**
 * returns the size of the heap
 */
int getSize(HeapP heap);

/**
 * returns the max size of the heap
 */
int getMaxSize(HeapP heap);

/**
 * prints the entire heap
 */
void printHeap(HeapP heap);


#endif /* DYNAMICHEAP_H_ */
