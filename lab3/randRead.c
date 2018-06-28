#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
	FILE *fp;

	//make sure correct number of paramaters has been entered
	if (argc < 2 || argc > 2)
	{
		printf("\nInvalid Parameters\n");
		return 1;
	}

	//open file
	fp = fopen(argv[1], "r");

	//make sure file is valid
	if (fp == NULL)
	{
		printf("\nThe file %s could not be opened\n", argv[1]);
		return 1;
	}

	int randOffset;
	int ch;

	//while loop to check if the end of the file has been reached
	while (ch != EOF)
	{
		//generate random number of bytes to jump forward in file
		randOffset = rand() % 100;
		fseek(fp, randOffset, SEEK_CUR);
		//read the current character
		ch = getc(fp);
	}

	fclose(fp);
}
