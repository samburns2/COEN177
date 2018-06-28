/*
 * Sam Burns
 * COEN 177L
 * F 2:15
 * Lab 1 Task 2
 *
 * This program creates EXACTLY 8 child processes (not including the initial process.
 * Each process has only 1 child.
 */

#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int main (void)
{
	int i, status;

	//print inital pid
	printf("\nMain process: %d\n", getpid());

	//loop to create 8 children
	for (i = 0; i < 8; i++)
	{
		if (fork() != 0)
		{
			waitpid(-1, &status, 0);
			break;
		}

		//Print pids
		else
		{
			printf("\nParent (%d): %d\n", i + 1, getppid());
			printf("Child (%d): %d\n", i + 1, getpid());
		}
	}
}
