/*************************************************************** 
 * Student Name: Jeff Morton
 * File Name: Main.c
 * Assignment Number: 4
 * Date Due: April 5, 2016
 * 
 *  Created on: Mar 29, 2016
 *      Author: Jeff Morton
 ***************************************************************/


#include "Seeder.h"
#include "BinPacker.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



/**
 * the main function
 */
int main(int argc, char *argv[])
{
	if ( (argc==2) && (strcmp(argv[1],"-Debug")==0) )
		fprintf(stdout,"Debug not implemented\n");

	seedItems(500);
	ItemArrayP items = readItems();
	int size = items->size;
	//fprintf(stdout, "Finished Reading Items\n");

	//Online Calculations
	BinArrayP onlineFirstFitBins = getBins( size );
	firstFit( onlineFirstFitBins, items );
	//fprintf(stdout, "Online First Fit Finished\n");


	BinArrayP onlineNextFitBins = getBins( size );
	resetItems( items );
	nextFit ( onlineNextFitBins, items );
	//fprintf(stdout, "Online Next Fit Finished\n");


	BinArrayP onlineBestFitBins = getBins( size );
	resetItems( items );
	bestFit ( onlineBestFitBins, items );
	//fprintf(stdout, "Online Best Fit Finished\n");



	//Offline Calculations
	BinArrayP offlineFirstFitBins = getBins( size );
	resetItems( items );
	sortItems( items );
	firstFit( offlineFirstFitBins, items );
	//printBins( offlineFirstFitBins );
	//fprintf(stdout, "Offline First Fit Finished\n");


	BinArrayP offlineBestFitBins = getBins( size );
	resetItems( items );
	sortItems( items );
	bestFit ( offlineBestFitBins, items );
	//printBins( offlineBestFitBins );
	//fprintf(stdout, "Offline Best Fit Finished\n");

	resetItems( items );
	sortItems( items );
	BinArrayP searchBasedBins = searchBasedPacking( items );

	fprintf(stdout, "      Policy      | Total Bins Used\n");
	fprintf(stdout, "Search-based      | %i\n", searchBasedBins->binsUsed );
	fprintf(stdout, "Online Algorithm  |\n");
	fprintf(stdout, "    First Fit     | %i\n", onlineFirstFitBins->binsUsed );
	fprintf(stdout, "    Next Fit      | %i\n", onlineNextFitBins->binsUsed );
	fprintf(stdout, "    Best Fit      | %i\n", onlineBestFitBins->binsUsed );
	fprintf(stdout, "Offline Algorithm |\n");
	fprintf(stdout, "    First Fit     | %i\n", offlineFirstFitBins->binsUsed );
	fprintf(stdout, "    Best Fit      | %i\n", offlineBestFitBins->binsUsed );


	//fprintf(stdout, "\nSearch Based Bin Packing:\n");
	//printBins(searchBasedBins);

	//fprintf(stdout, "\nOnline First Fit Bin Packing:\n");
	//printBins(onlineFirstFitBins);

	//fprintf(stdout, "\nOnline Next Fit Bin Packing:\n");
	//printBins(onlineNextFitBins);

	//fprintf(stdout, "\nOnline Best Fit Bin Packing:\n");
	//printBins(onlineBestFitBins);

	//fprintf(stdout, "\nOffline First Fit Bin Packing:\n");
	//printBins(offlineFirstFitBins);

	//fprintf(stdout, "\nOffline Best Fit Bin Packing:\n");
	//printBins(offlineBestFitBins);


	return(0);
}
