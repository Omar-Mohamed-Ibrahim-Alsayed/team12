#include <stdio.h>
#include <stdlib.h>
#include "pm.h"
#include <sys/stat.h>
#include <minix/callnr.h>
#include <minix/endpoint.h>
#include <minix/com.h>
#include <minix/vm.h>
#include <signal.h>
#include <libexec.h>
#include <sys/ptrace.h>
#include "mproc.h"
#include "vm.h"

int parseArguments(int argc, char*argv[])
 {
 int tableSize;
 if(argc == 2 && (tableSize = atoi(argv[1])))
 { 
return tableSize;
 }
 }
 
int isInMemory(int pageRequest, int *pageTable, int tableSize) 
{ 
int i; 
for (i = 0; i < tableSize; i++) 
{
 if(pageRequest == pageTable[i]) 
{
  return 1;
 }
}
 return 0;
}

void fifo_page_replace(smaller_inner_pagetable* pt){
	
	//initialize all needed variables to check if a replacement is needed. 
	int tableSize = pt[0].number_of_pagetables; 
	int pageRequest, pageTableIndex = 0,
	numRequests = 0, 
	numMisses = 0;
	ssize_t bytesRead = &pt[0];
	int i; 
	while(bytesRead) != -1)
		{
		pageRequest = list_of_smaller_pagetables[pageTableIndex].page_table_query; 
		if (pageRequest == 0)
			{ 
			continue;
			}
		numRequests++;
		if (!isInMemory(pageRequest, pt, tableSize))
			{
			numMisses++;
			if (pageTableIndex < tableSize) 
				{
				//still have room in page table
				pt[pageTableIndex++] = pageRequest;
				}
			else
			{
			// Algorithm for FIFO 
			for (i=0; i<tableSize;i++)
				{
				pt[i]=pt[i+1];
				}
			pt[tableSize-1]=pageRequest;
			} 
		}
	//update something in pageTable so that lru and second chance work correctly 
		else { 

			printf("%d is already in table, no page faults.\n", pageRequest); 
			}
		}	 
	printf("Hit rate = %f\n", (numRequests - numMisses)/(double)numRequests); 
	free(pt);
	}
