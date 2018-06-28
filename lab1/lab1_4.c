/*
 * Sam Burns
 * COEN 177L
 * F 2:15
 * Lab 1 Task 4
 *
 * This code creates a tree of processes with the following format:
 * Intial Process - Level 0
 * 3 Children = Level 1
 * 2 Children per level 1 child = Level 2
 * 2 children for the first 4 children of level 2, 0 for other 2 children - Level 3
 *
 * Total = 17 child processes
 *
 * Nested if statements check to see where child processes should be created and how many there should be.
 *
 * The first initial process has 3 children, but the children only have 2 child processes each.
 */

#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
	int i, status;
	//bool variable to check if the tree is on the maxLevel
	int lastLevel = 0;
	int depth = 3;

	//initial process
	printf("\nMain Process: %d\n", getpid());
	
	//for loop to create processes for a tree of depth 3
	for (i = 0; i < depth; i++)
	{
		if (fork() != 0)
		{
			waitpid(-1, &status, 0);
			if (fork() != 0)
			{
				waitpid(-1, &status, 0);

				// make sure initial process has 3 children, the rest have 2
				if (i == 0)
				{
					lastLevel = 1; 
					if (fork() != 0)
					{
						waitpid(-1, &status, 0);
						break;
					}			
					else 
						printf("\nParent ID: %d\nChild ID: %d\n", getppid(), getpid());
				}
				else
					break;
			} 
			else 
			{
				printf("\nParent ID: %d\nChild ID: %d\n", getppid(), getpid());
				if(lastLevel) 
					return(0);
			}	
		} 
		else 
		{
			printf("\nParent ID: %d\nChild ID: %d\n", getppid(), getpid());
			if(lastLevel) 
				return(0);
		}	
  }
	return(0);
}
