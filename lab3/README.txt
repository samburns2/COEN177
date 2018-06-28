Sam Burns
COEN177 Lab
F 2:15
Lab 3 ReadMe

For this lab, the objective was to investigate the performance of a computer's file system. In order to do this, we created 3 diffferent files of different sizes: 1 GB, 5 GB, and 10GB, and then created programs to read through them sequentially and read through them randomly. The logic for the sequential read, seqRead.c, is quite simple. THe program opens the file, makes sure that the file is valid, then reads every single character in that file, until the EOF, sequentially. The random read function, randRead.c, reads through the file, obviously, randomly. The program generates a random number by modding rand() by 100, and then jumps forward that random number of bytes and does so until the EOF. In theory, and in practice, the randRead function is faster since not every single character is faster, as shown below:


seqRead.c

Time of exeuction

1GB File:
1) 5.934s
2) 5.915s
3) 5.921s
4) 5.919s
5) 5.865s
Avg: 5.9108s

5GB File:
1) 29.132s
2) 29.114s
3) 29.066s
4) 29.153s
5) 29.004s
Avg: 29.094s

10GB File:
1) 58.646s
2) 58.599s
3) 57.955s
4) 57.473s
5) 57.675s
Avg: 58.070

randRead.c

Time of execution

1GB File:
1) 2.252s
2) 2.221s
3) 2.209s
4) 2.218s
5) 2.252s
Avg: 2.230s

5GB File:
1) 16.696s
2) 10.702s
3) 10.632s
4) 10.606s
5) 10.615s
Avg: 11.850

10GB File:
1) 27.515s
2) 21.153s
3) 20.913s
4) 21.051s
5) 21.058s
Avg: 22.338s

However, one thing I found interesting, was that when trying to make randRead faster, I had to make sure to mod rand() by a larger number. Modding by 100 essentially made the program about twice as fast as seqRead. However, when I initially made randRead, I modded rand() by 10. Again, in theory, this should still be faster, as there's an 80% chance that the character that will be read is more than 1 byte ahead. However, when I was testing this, randRead was actually about 3 times slower. I figured that this was because the rand() function is actually a pretty slow function, so running it that many times when reading through the files is very time costly. So, when modding by 100, that effect is less noticeable, since randRead ends up being faster. I found this very interesting that even when the program was supposed to be faster, it was actually much slower. Again, I think this is because the rand() function is a slow function, and using it to calculate a random number that many times is time costly.

With regards to the computer's file system, I think this lab helped illustrate that the implementation of functions dealing with the file system has a large effect on the performance. If the system is constantly operating on files, the implementation of the system's file reading algorithm is extremely important, since something as simple as the rand() function can have a very large impact of the effectiveness of the algorithm with regards to time.


