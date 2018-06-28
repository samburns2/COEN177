/*
 * Sam Burns
 * COEN177L
 * F 2:15
 * Lab 1 Task 1
 *
 * This code is a simple shell program that checks for requests to run a process
 *
 * The shell will terminate if the user enters the string "exit"
 */

#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>

int main (void)
{
	int status;
	char input[30];

//infinite loop to check for requests
	while (1)
	{
		printf("Enter program name to run program. Enter 'exit' to terminate shell.\n");
		scanf("%s", input);

		//check if user wants to exit
		if (strcmp("exit", input) == 0)
			break;

		if (fork() != 0)
		{
			//parent code
			waitpid(-1, &status, 0);
		}
		else
		{
			//child code
			execve(input , NULL, 0);
			break;
		}	
	}
}
