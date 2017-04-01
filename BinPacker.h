/*************************************************************** 
 * Student Name: Jeff Morton
 * File Name: BinPacker.h
 * Assignment Number: 4
 * Date Due: April 5, 2016
 * 
 *  Created on: Mar 30, 2016
 *      Author: Jeff Morton
 ***************************************************************/

#ifndef BINPACKER_H_
#define BINPACKER_H_


#define BIN_SIZE 1.0

#define TRUE 1
#define FALSE 0


typedef struct Item *ItemP;
typedef struct Item
{
	float size;
	ItemP next;
} Item;


typedef struct Bin
{
	float sizeUsed, sizeFree;
	int numItems;
	ItemP first;
}Bin, *BinP;


typedef struct ItemArray
{
	ItemP *items;
	int size;
}ItemArray, *ItemArrayP;


typedef struct BinArray
{
	BinP *bins;
	int binsTotal, binsUsed;
}BinArray, *BinArrayP;




/**
 * Allocates memory for a new bin and initializes it
 * @return BinP the newly created bin
 */
BinP newBin();

/**
 * allocates and initializes a new item
 * @param {float} size - the size of the item
 * @return ItemP the item created
 */
ItemP newItem( float size );

/**
 * reads items in from items.txt, creates items for them, stores them in an array, then returns that array
 * @return ItemArrayP the array of items
 */
ItemArrayP readItems();

/**
 * creates an array of size number of bins
 * @param {int} size - the number of bins to create
 * @return BinArrayP the array of bins
 */
BinArrayP getBins( int size );

/**
 * First fit method of packing the bins
 * @param {BinArrayP} binArray - the array of bins to be packed
 * @param {ItemArrayP} itemArray - the array of items to be packed
 */
void firstFit( BinArrayP binArray, ItemArrayP itemArray );

/**
 * Next fit method of packing the bins
 * @param {BinArrayP} binArray - the array of bins to be packed
 * @param {ItemArrayP} itemArray - the array of items to be packed
 */
void nextFit( BinArrayP binArray, ItemArrayP itemArray );

/**
 * Best fit method of packing the bins
 * @param {BinArrayP} binArray - the array of bins to be packed
 * @param {ItemArrayP} itemArray - the array of items to be packed
 */
void bestFit( BinArrayP binArray, ItemArrayP itemArray );

/**
 * sorts items in the ItemArray passed in descending order
 * @param {ItemArrayP} itemArray - the array of items to sort
 */
void sortItems( ItemArrayP itemArray );

/**
 * prints the item array passed
 * @param {ItemArrayP} itemArray - the item array to print
 */
void printArray( ItemArrayP itemArray );

/**
 * prints the bin array passed
 * @param {BinArrayP} binArray - the item array to print
 */
void printBins( BinArrayP binArray );

/**
 * executes a search based genetic algorithm that calculates 50 permutations of the item array passed
 * keeps the best permutation (determined by the number of bins resulting from best fit algorithm)
 * returns the best bin packing achieved
 * @param {ItemArrayP} items - the array of items to pack
 * @return BinArrayP - the best packed array of bins after 50 permutations
 */
BinArrayP searchBasedPacking( ItemArrayP items );

/**
 * Sets the next pointer of every item in the array to null
 * @param {ItemArrayP} items - the array of items to reset
 */
void resetItems( ItemArrayP items );


#endif /* BINPACKER_H_ */
