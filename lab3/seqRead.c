#include <stdio.h>

int main (int argc, char *argv[])
{
	FILE *fp;

	//make sure correct # of parameters was entered
	if (argc < 2 || argc > 2)
	{
		printf("\nInvalid Parameters\n");
		return 1;
	}

	fp = fopen(argv[1], "r");

	//make sure file is valid
	if (fp == NULL)
	{
		printf("\nThe file %s could not be opened\n", argv[1]);
		return 1;
	}

	//while loop to traverse the file and read every character
	int ch;
	while (ch = fgetc(fp) != EOF)
	{
	}

	fclose(fp);
}
