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
#include <stdio.h>
#include <stdlib.h>

struct Node {
	int pageNum;
	Node* next;
	Node* prev;
};
	Node* head;
	Node* tail;
Node* GetNewNode(int pageRequest) {
	Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	newNode->pageNum = pageRequest;
	newNode->next = NULL;
	newNode->prev = NULL;
	return newNode;
	}
void InsertAtTail(int pageRequest) {
	Node* myNode = GetNewNode(pageRequest);
	if (head == NULL)
		{
		head = myNode;
		tail = myNode;
		return;
		}
	tail->next = myNode;
	myNode->next = NULL;
	myNode->prev = tail;
	tail = myNode;
	return;
	}
	
void PopAtHead(void) {
	Node* temp = head;
	head = head->next;
	head->prev = NULL;
	temp->next = NULL;
	free(temp);
	return;
	}
	
int parseArguments(int argc, char*argv[]) {
	int tableSize;
	if(argc == 2 && (tableSize = atoi(argv[1])))
		{
		return tableSize;
		}
	fprintf(stderr, "Wrong arguments. Pass tableSize as an argument\n");
	exit(-1);
	}
	
Node* isInMemory(int pageRequest, int tableSize) {
	Node* check = head;
	while (check != NULL)
		{
		if (check->pageNum == pageRequest)
			{
			return check;
			}
			check = check->next;
			}
	return NULL;
}

void lru_page_replace(smaller_inner_pagetable* pt) {
	//initialize all needed variables to check if a replacement is needed.
	int tableSize = pt[0].number_of_pagetables;
	int pageRequest, pageTableIndex = 0, numRequests = 0, numMisses = 0;
	ssize_t bytesRead = &pt[0];
	int i;
	head = NULL;
	tail = NULL;
	while(bytesRead != -1)
		{
		pageRequest = list_of_smaller_pagetables[pageTableIndex].page_table_query;
		if (pageRequest == 0)
			{
			continue;
			}
		numRequests++;
		Node* nodeSelected = isInMemory(pageRequest, tableSize);
		if (nodeSelected == NULL)
			{
			numMisses++;
			printf("before if pagetabe<tablesize\n");
			if (pageTableIndex < tableSize)
				{ //still have room in page table
				InsertAtTail(pageRequest);
				pageTableIndex++;
				}
			else
			{		 // TODO implement a page replacement algorithm
					// Algorithm for LRU
				PopAtHead();
				InsertAtTail(pageRequest);
			}
		}//update something in pageTable so that lru and second chance work correctly
		else
		{
			if (nodeSelected == head && nodeSelected != tail)
			{
			head = head->next;
			head->prev = NULL;
			nodeSelected->next = NULL;
			nodeSelected->prev = tail;
			tail->next = nodeSelected;
			tail = nodeSelected;
			}
		else if (nodeSelected != head && nodeSelected != tail)
			{
			nodeSelected->prev->next = nodeSelected->next;
			nodeSelected->next->prev = nodeSelected->prev;
			nodeSelected->prev = tail;
			nodeSelected->next = NULL;
			tail->next = nodeSelected;
			tail = nodeSelected;
			}
		}
		Node* nodeP = head;
	}
	printf("Hit rate = %f\n", (numRequests - numMisses)/(double)numRequests);
	free(input);
	Node* nodeSelected;
	while(head != NULL)
		{
		nodeSelected = head;
		head = head->next;
		free(nodeSelected);
		}
}