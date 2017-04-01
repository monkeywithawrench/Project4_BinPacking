/*************************************************************** 
 * Student Name: Jeff Morton
 * File Name: BinPacker.c
 * Assignment Number: 4
 * Date Due: April 5, 2016
 * 
 *  Created on: Mar 30, 2016
 *      Author: Jeff Morton
 ***************************************************************/

#include "BinPacker.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "DynamicHeap.h"

#define PERMUTATION_COUNT 250


/*			Function Prototypes			*/

/**
 * adds the item passed to the last item in the linkedlist
 * @param {ItemP} list - the item containing the linkedList
 * @param {ItemP} item - the item to add
 */
void addItemToList( ItemP list, ItemP item );

/**
 * prints the linkedList of items passed (the bin)
 * @param {ItemP} item - the linkedList to print
 */
void printBin( ItemP item );

/**
 * Clones the itemArray passed and sets all next pointers to NULL
 * @param {ItemArrayP} srcItems - the array of items to clone
 * @param {ItemArrayP} newItems - the new array of cloned items
 * @return ItemArrayP - the new array of items
 */
ItemArrayP cloneItemArray( ItemArrayP srcItems, ItemArrayP newItems );

/**
 * Resets the array of bins so that they can be repacked.
 * @param {BinArrayP} bins - the array of bins to reset
 */
void resetBins( BinArrayP bins );

/**
 * randomly permutes the ItemArray passed
 * @param {ItemArrayP} items - the itemarray to permute
 */
void permuteItems( ItemArrayP items );

/*			End Function Prototypes		*/




/**
 * Allocates memory for a new bin and initializes it
 * @return BinP the newly created bin
 */
BinP newBin()
{
	BinP bin = /* (Bin) */ malloc(sizeof(Bin));
	if(bin == NULL)	//Checks malloc success.
	{
		fprintf(stderr, "ERROR! Bin Malloc failed!");
		return(bin);
	}
	bin->sizeFree = BIN_SIZE;
	bin->sizeUsed = 0.0;
	bin->numItems = 0;
	bin->first = NULL;
	return( bin );
}


/**
 * allocates and initializes a new item
 * @param {float} size - the size of the item
 * @return ItemP the item created
 */
ItemP newItem( float size )
{
	ItemP item = /* (Item) */ malloc(sizeof(Item));
	if(item == NULL)	//Checks malloc success.
	{
		fprintf(stderr, "ERROR! Item Malloc failed!");
		return(item);
	}
	item->next = NULL;
	item->size = size;
	return(item);
}


/**
 * reads items in from items.txt, creates items for them, stores them in an array, then returns that array
 * @return ItemArrayP the array of items
 */
ItemArrayP readItems()
{
	FILE *inFile = fopen("items.txt","r");
	if( inFile == NULL )
	{
		fprintf(stderr, "file \"items.txt\" could not be open!!! Program exiting!\n");
		exit(0);
	}

	int size;
	fscanf(inFile, "%i", &size);

	ItemArrayP itemArray = /* (ItemArray) */ malloc(sizeof(ItemArray));
	if(itemArray == NULL)	//Checks malloc success.
	{
		fprintf(stderr, "ERROR! ItemArray Struct Malloc failed!");
		return(itemArray);
	}

	ItemP *items = /* (Item) */ malloc(sizeof(ItemP)*size);
	if(items == NULL)	//Checks malloc success.
	{
		fprintf(stderr, "ERROR! Item Array Malloc failed!");
		return(itemArray);
	}

	itemArray->items = items;
	itemArray->size = size;

	int i=0;
	while( i<itemArray->size )
	{
		float temp2;
		fscanf(inFile, "%f", &temp2);
		if(temp2 > BIN_SIZE)
		{
			fprintf(stdout, "Item of size %f exceeds bin size of %f, item thrown out!\n", temp2, BIN_SIZE);
			itemArray->size--;
		}
		else
		{
			ItemP tempItem = newItem(temp2);
			items[i] = tempItem;
			i++;
		}
	}

	return( itemArray );
}


/**
 * creates an array of size number of bins
 * @param {int} size - the number of bins to create
 * @return BinArrayP the array of bins
 */
BinArrayP getBins( int size )
{
	BinArrayP binArray = /* (BinArray) */ malloc(sizeof(BinArray));
	if(binArray == NULL)	//Checks malloc success.
	{
		fprintf(stderr, "ERROR! BinArray Struct Malloc failed!");
		return(binArray);
	}

	BinP *bins = /* (Bin) */ malloc(sizeof(BinP)*size);
	if(bins == NULL)	//Checks malloc success.
	{
		fprintf(stderr, "ERROR! Bin Array Malloc failed!");
		return(binArray);
	}

	binArray->bins = bins;
	binArray->binsTotal = size;
	binArray->binsUsed = 0;

	int i;
	for( i=0; i<size; i++ )
	{
		BinP temp = newBin();
		bins[i] = temp;
	}
	return( binArray );
}


/**
 * First fit method of packing the bins
 * @param {BinArrayP} binArray - the array of bins to be packed
 * @param {ItemArrayP} itemArray - the array of items to be packed
 */
void firstFit( BinArrayP binArray, ItemArrayP itemArray )
{
	int i, j;
	for( i=0; i<itemArray->size; i++ )
	{
		int placed = FALSE;
		ItemP item = itemArray->items[i];
		j=0;
		while( !placed && (j<binArray->binsTotal) )
		{
			//fprintf(stderr, "i:%i j:%i\n", i, j);
			if( binArray->bins[j]->sizeFree >= item->size )
			{
				//fprintf(stderr, "i:%i j:%i\n", i, j);
				BinP bin = binArray->bins[j];
				if( bin->first == NULL )
					bin->first = item;
				else
					addItemToList( bin->first, item );
				bin->sizeFree -= item->size;
				bin->sizeUsed += item->size;
				placed = TRUE;
				if( j >= binArray->binsUsed )
					binArray->binsUsed++;
			}
			j++;
		}
		if( !placed )
			fprintf(stdout, "Warning, item of size %f could not be placed in a bin!\n", item->size );
	}
	//should be done by now, returning
	return;
}


/**
 * Next fit method of packing the bins
 * @param {BinArrayP} binArray - the array of bins to be packed
 * @param {ItemArrayP} itemArray - the array of items to be packed
 */
void nextFit( BinArrayP binArray, ItemArrayP itemArray )
{
	int i, j=0;
	for( i=0; i<itemArray->size; i++ )
	{
		int placed = FALSE;
		ItemP item = itemArray->items[i];
		while( !placed && (j<binArray->binsTotal) )
		{
			if( binArray->bins[j]->sizeFree >= item->size )
			{
				BinP bin = binArray->bins[j];
				if( bin->first == NULL )
					bin->first = item;
				else
					addItemToList( bin->first, item );
				bin->sizeFree -= item->size;
				bin->sizeUsed += item->size;
				placed = TRUE;
				if( j >= binArray->binsUsed )
					binArray->binsUsed++;
			}
			else
			//if( binArray->bins[j]->sizeFree < item->size )
				j++;
		}
		if( !placed )
			fprintf(stdout, "Warning, item of size %f could not be placed in a bin!\n", item->size );
	}
	//should be done by now, returning
	return;
}


/**
 * Best fit method of packing the bins
 * @param {BinArrayP} binArray - the array of bins to be packed
 * @param {ItemArrayP} itemArray - the array of items to be packed
 */
void bestFit( BinArrayP binArray, ItemArrayP itemArray )
{
	int i=0, j=0;
	for( i=0; i<itemArray->size; i++ )
	{
		int binIndex = 0;
		float binSize = 1.0;
		ItemP item = itemArray->items[i];
		for( j=0; j<=binArray->binsUsed; j++ )
		{
			if( j != binArray->binsTotal )
			{
				float sizeFree = binArray->bins[j]->sizeFree;
				if( (sizeFree >= item->size) && ((sizeFree - item->size) < binSize) )
				{
					binIndex=j;
					binSize = sizeFree - item->size;
				}
			}
		}
		BinP bin = binArray->bins[binIndex];
		if( bin->first == NULL )
			bin->first = item;
		else
			addItemToList( bin->first, item );
		bin->sizeFree -= item->size;
		bin->sizeUsed += item->size;
		if( binIndex >= binArray->binsUsed )
			binArray->binsUsed++;
	}
	return;
}


/**
 * adds the item passed to the last item in the linkedList
 * @param {ItemP} list - the item containing the linkedList
 * @param {ItemP} item - the item to add
 */
void addItemToList( ItemP list, ItemP item )
{
	if( list->next == NULL)
	{
		list->next = item;
		return;
	}
	else
		addItemToList(list->next, item);
	return;
}


/**
 * sorts items in the ItemArray passed in descending order
 * @param {ItemArrayP} itemArray - the array of items to sort
 */
void sortItems( ItemArrayP itemArray )
{
	HeapP heap = newHeap( itemArray->size );
	int i;
	for( i=0; i<itemArray->size; i++ )
	{
		ItemP item = itemArray->items[i];
		heapInsert( heap, (double)item->size, item);
	}
	int size = itemArray->size;
	for( i=0; i<itemArray->size; i++ )
		itemArray->items[size-i-1] = heapExtract(heap); //work backwards through array since it's a min heap
	//itemArray is now sorted!
	return;
}


/**
 * prints the item array passed
 * @param {ItemArrayP} itemArray - the item array to print
 */
void printArray( ItemArrayP itemArray )
{
	int i;
	for( i=0; i<itemArray->size; i++)
		fprintf(stdout, "Item[%i]: %f\n", i, itemArray->items[i]->size);
	return;
}


/**
 * prints the bin array passed
 * @param {BinArrayP} binArray - the item array to print
 */
void printBins( BinArrayP binArray )
{
	int i;
	for( i=0; i<binArray->binsUsed; i++)
	{
		fprintf(stdout, "Bin[%i]: ", i);
		printBin(binArray->bins[i]->first);
		fprintf(stdout, "\n");
	}
	return;
}


/**
 * prints the linkedList of items passed (the bin)
 * @param {ItemP} item - the linkedList to print
 */
void printBin( ItemP item )
{
	fprintf(stdout, "%f, ", item->size);
	if(item->next != NULL)
		printBin( item->next );
	return;
}


/**
 * Sets the next pointer of every item in the array to null
 * @param {ItemArrayP} items - the array of items to reset
 */
void resetItems( ItemArrayP items )
{
	int i;
	for( i=0; i<items->size; i++ )
		items->items[i]->next = NULL;
	return;
}


/**
 * Clones the itemArray passed and sets all next pointers to NULL
 * @param {ItemArrayP} srcItems - the array of items to clone
 * @param {ItemArrayP} newItems - the new array of cloned items
 * @return ItemArrayP - the new array of items
 */
ItemArrayP cloneItemArray( ItemArrayP srcItems, ItemArrayP newItems )
{
	resetItems(newItems);
	int i;
	for( i=0; i<srcItems->size; i++ )
		newItems->items[i]->size = srcItems->items[i]->size;
	return(newItems);
}


/**
 * Resets the array of bins so that they can be repacked.
 * @param {BinArrayP} bins - the array of bins to reset
 */
void resetBins( BinArrayP bins )
{
	int i;
	for( i=0; i<bins->binsTotal; i++ )
	{
		bins->bins[i]->first = NULL;
		bins->bins[i]->numItems = 0;
		bins->bins[i]->sizeFree = 1.0;
		bins->bins[i]->sizeUsed = 0.0;
	}
	bins->binsUsed = 0;
	return;
}


/**
 * executes a search based genetic algorithm that calculates 50 permutations of the item array passed
 * keeps the best permutation (determined by the number of bins resulting from best fit algorithm)
 * returns the best bin packing achieved
 * @param {ItemArrayP} items - the array of items to pack
 * @return BinArrayP - the best packed array of bins after 50 permutations
 */
BinArrayP searchBasedPacking( ItemArrayP items )
{
	sortItems(items); //initial sort of item array.
	BinArrayP bins1 = getBins(items->size);
	bestFit(bins1, items);
	srand((unsigned int)time(NULL)); //seed rand()

	BinArrayP bins2 = getBins(items->size);
	ItemArrayP items2 = readItems();
	cloneItemArray(items, items2);

	int i;
	for( i=0; i<PERMUTATION_COUNT; i++ )
	{
		permuteItems(items2);
		bestFit( bins2, items2 );
		if( bins2->binsUsed < bins1->binsUsed )
		{
			BinArrayP tempBins = bins1;
			ItemArrayP tempItems = items;
			bins1 = bins2;
			bins2 = tempBins;
			items = items2;
			items2 = tempItems;
			cloneItemArray(items, items2);
			resetBins(bins2);
		}
		else
		{
			cloneItemArray(items, items2);
			resetBins(bins2);
		}
	}
	return(bins1);
}


/**
 * randomly permutes the ItemArray passed
 * @param {ItemArrayP} items - the itemarray to permute
 */
void permuteItems( ItemArrayP items )
{
	int i = rand() % items->size;
	int j = rand() % items->size;
	ItemP item = items->items[i];
	items->items[i] = items->items[j];
	items->items[j] = item;
	return;
}




