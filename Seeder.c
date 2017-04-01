/*************************************************************** 
 * Student Name: Jeff Morton
 * File Name: Seeder.c
 * Assignment Number: 4
 * Date Due: April 5, 2016
 * 
 *  Created on: Mar 29, 2016
 *      Author: Jeff Morton
 ***************************************************************/

#include "Seeder.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>





/**
 * Seeds the items.txt file
 * @param {int} numItems - the number of items to generate
 */
void seedItems( int numItems )
{
	FILE *outFile = fopen("items.txt","w");
	if( outFile == NULL )
	{
		fprintf(stderr, "file \"items.txt\" could not be open!!! Program exiting!\n");
		exit(0);
	}

	fprintf(outFile, "%i\n", numItems);

	srand((unsigned int)time(NULL)); //seed rand()
	int i=0;
	float temp;
	for( i=0; i<numItems; i++)
	{
		temp = (double)rand() / RAND_MAX;
		fprintf(outFile, "%f\n", temp);
	}
	fclose(outFile);

	return;
}
