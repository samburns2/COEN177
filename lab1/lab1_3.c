/*
 * Sam Burns
 * COEN 177L
 * F 2:15
 * Lab 1 Task 3
 *
 * This program creates EXACTLY 12 child processes (not including intial process).
 *
 * Each process only creats 3 children, creating a tree structure.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main ()
{
	//maxHeight and level check to see are variable to check if tree is full
	int maxHeight = 3;
	int level = 1;

	int status;

	printf("\nMain process: %d\n", getpid());

	int i;
	for (i = 0; i < 3; i++)
	{
		int pid = fork();

		if (pid == 0)
		{
			level = level + 1;
			printf("\nParent: %d\nChild: %d\n", getppid(), getpid());

			i = -1;
		}
		else
			waitpid(-1, &status, 0);

		//check to see if the tree is at the max height
		if (level >= maxHeight)
			return 0;
	}
}
