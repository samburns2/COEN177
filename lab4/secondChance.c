#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_MEMORY_SIZE 500

typedef struct pageTableEntry PTE;
typedef struct pageTable PT;

struct pageTableEntry
{
	struct pageTableEntry *next;
	struct pageTableEntry *prev;
	int pageRequest;
	int reference;
};

struct pageTable
{
	struct pageTableEntry *head;
	int tableSize;
	int count;
};

int isInMemory(int page, PT *pageTable)
{
	PTE *currentPTE = pageTable->head->next;

	int i;
	for (i = 0; i < pageTable->count; i++)
	{
		if (currentPTE->pageRequest == page)
			return 1;
		currentPTE = currentPTE->next;
	}
	return 0;
}

void removeOldest(PT *pageTable)
{
	assert(pageTable != NULL && pageTable->count > 0);

	PTE *currentPTE = pageTable->head->next;

	int i;
	for (i = 0; i < pageTable->count; i++)
	{
		if (currentPTE->reference == 0)
			break;
		else
			currentPTE->reference = 0;

		currentPTE = currentPTE->next;
	}

	
	currentPTE->prev->next = currentPTE->next;
	currentPTE->next->prev = currentPTE->prev;

	free(currentPTE);
	pageTable->count--;
	return;
}

void addEnd(int page, PT *pageTable)
{
	PTE *newPTE = malloc(sizeof(PTE));
	assert(newPTE != NULL);

	newPTE->pageRequest = page;
	newPTE->next = pageTable->head;
	newPTE->prev = pageTable->head->prev;
	newPTE->reference = 0;

	pageTable->head->prev->next = newPTE;
	pageTable->head->prev = newPTE;
	pageTable->count++;
}

void setReference(int page, PT *pageTable)
{
	PTE *currentPTE = pageTable->head->next;
	int i;
	for (i = 0; i < pageTable->count; i++)
	{
		if (currentPTE->pageRequest == page)
			break;

		currentPTE = currentPTE->next;
	}

	currentPTE->reference = 1;
}

int main (int argc, char *argv[])
{
	if(argc < 2)
	{
		fprintf(stderr, "Improper usage! Provide size of page table as argument.\n");
		return -1;
	}

	PT *pageTable = malloc(sizeof(PT) * MAX_MEMORY_SIZE);
	assert (pageTable != NULL);
	pageTable->tableSize = atoi(argv[1]);
	pageTable->count = 0;

	pageTable->head = malloc(sizeof(PTE));
	assert(pageTable->head != NULL);
	
	pageTable->head->next = pageTable->head;
	pageTable->head->prev = pageTable->head;

	char *input = NULL;
	ssize_t bytesRead;
	size_t inputAllocated = 0;
	int pageRequest = 0;

	int pageFaults = 0;
	int memoryAccesses = 0;

	while ((bytesRead = getline(&input, &inputAllocated, stdin)) != EOF)
	{
		pageRequest = atoi(input);
		if (pageRequest == 0)
			continue;

		memoryAccesses++;

		if (!isInMemory(pageRequest, pageTable))
		{
			printf("Page number %d caused a page fault.\n", pageRequest);

			if (pageTable->count < pageTable->tableSize)
			{
				addEnd(pageRequest, pageTable);
			}
			else
			{
				//TODO implement a page replacement algorithm
				removeOldest(pageTable);
				addEnd(pageRequest, pageTable);
			}
			pageFaults++;
		}
		else
			setReference(pageRequest, pageTable);
	}

	int i;
	for (i = 0; i < pageTable->count; i++)
		removeOldest(pageTable);
	
	free(pageTable->head);
	free(pageTable);
	free(input);
	
//	printf("\nPage Faults: %d\n", pageFaults);
//	printf("Memory Accesses: %d\n", memoryAccesses);
	return 0;
}
