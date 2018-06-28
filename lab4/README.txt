Sam Burns
COEN 177L
F 2:15
Lab 4 Readme

In this folder, there are 4 implementations of difference page replacement algorithms. The page table in each algorithm was implemented using a DEQUE, with a dummy node named head to signify the start of the deque. The 4 page replacement algorithms are First In, Firt Out (FIFO), Least Recently Used (LRU), Least Frequently Used (LFU), and Second Chance (secondChance). Each implementation has different helper functions to help it implement the page replacement algorithm correctly.





FIFO.c
FIFO replaces the first page in the page table with the page that had a page fault. The oldest page in the page table is at the head of the deque, while the newest page table is at the end of the deque. It has 3 helper functions:

isInMemory: O(N) time
This function move sequentially throug the page table to check if the given page is already in the page table. It returns 1 if the page is in the page table, and 0 if it is not.

removeOldest: O(1) time
This function simply removes the oldest page in the page table, by first changing the pointers to not point to the first page in the page table, and then freeing that memory.

addEnd: O(1) time
This function adds a new page to the end of the page table.

FIFO Page Miss Rates

Page Table Size 10
Page Faults: 5075
Memory Accesses: 5120

Page Table Size 50
Page Faults: 4865
Memory Accesses: 5120

Page Table Size 100
Page Faults: 4591
Memory Accesses: 5120

Page Table Size 250
Page Faults: 3758
Memory Accesses: 5120

Page Table Size 500
Page Faults: 2616
Page Accesses: 5120

As we can see by the page table of size 10, using the FIFO algorithm results in a page fault for almost every memory access. While the page faults go down as the table size increases, this is to be expected. FIFO is not a very efficient algorithm because it does not take into account how often certain pages are accessed.





LRU.c
LRU replaces the page that was used the least recently with the page that had a page fault. The first page in the page table is the least recently used while the last page in the page table is the most recently used. In order to keep track of how recently a page was accessed, there are a couple of helper functions:

isInMemory: O(N) time
This function move sequentially throug the page table to check if the given page is already in the page table. It returns 1 if the page is in the page table, and 0 if it is not.

addEnd: O(1) time
This function adds a new page to the end of the page table.

removeLRU: O(1) time
This function removes the least recently used page, which is the first page in the page table.

updateMRU: O(N) time
This function first finds the requested page in the page table, and then moves it to the end of the page table to signify it as the most recently used page. This function is used when a page that is already in the page table is requested.


LRU Page Miss Rates

Page Table Size 10
Page Faults: 5075
Memory Accesses: 5120

Page Table Size 50
Page Faults: 4860
Memory Accesses: 5120

Page Table Size 100
Page Faults: 4596
Memory Accesses: 5120

Page Table Size 250
Page Faults: 3726
Memory Accesses: 5120

Page Table Size 500
Page Faults: 2598
Memory Accesses: 5120

As we can see by the miss rates, LRU is not much more efficent than FIFO. 





LFU.c
LFU replaces the page that is used the least frequently with the page that had a page fault. In the case of a tight for the least frequently used page, the tie is broken by which page was used the least recently. The struct for LFU has a variable called numRequests which keeps track of how many times a page has been requested. LFU has a few helper functions to properly execute the algorithm:

isInMemory: O(N) time
This function move sequentially throug the page table to check if the given page is already in the page table. It returns 1 if the page is in the page table, and 0 if it is not.

addEnd: O(1) time
This function adds a new page to the end of the page table.

removeLFU: O(N) time
This function removes the least frequently used page. In order to find this, the function loops through the entire page table from least recently page used to most recently used page, and keeps track of which page has been accessed the least amount of times. In the event of a tie, the page that was used least recently is the page that will be removed.

updateMRU: O(N) time
This function first finds the requested page in the page table, and then moves it to the end of the page table to signify it as the most recently used page. This function is used when a page that is already in the page table is requested.


LFU Page Miss Rates

Page Table Size 10
Page Faults: 5081
Memory Accesses: 5120

Page Table Size 50
Page Faults: 4886
Memory Accesses: 5120

Page Table Size 100
Page Faults: 4667
Memory Accesses: 5120

Page Table Size 250
Page Faults: 3953
Memory Accesses: 5120

Page Table Size 500
Page Faults: 2808
Memory Acceses: 5120

As we can see, LFU results in more page faults than FIFO and LRU.





secondChance.c
secondChance is a modified version of FIFO, that tries to avoid throwing out heavily used pages. The PTEs have a reference bit, that is initally set to 0, and if the page is accesed while still in the page table, the reference bit is set to 0. Then replacement algorithm itself will not throw out a page that has it's reference bit as 0. If it sees a reference bit is 1, it will reset the reference bit to 0 and continue to search for a free page. In order to implement this, I had to modify the FIFO.c file to include a reference bit, and added a helper function to set the refrence bit to 1.

This is a valid page replacement algorithm because it is essentially a more fair version of FIFO. By trying to avoid throwing out heavily used pages, it makes sure that heavily used pages are more than likely going to stay in the page table. While it may not be the most effiecent way of replacing pages, it is definitely a valid algorithm due to the fact that it replaces pages in a similar way to FIFO, but takes into account how often they are used.

Here are the helper functions for the second chance algorithm:

isInMemory: O(N) time
This function move sequentially throug the page table to check if the given page is already in the page table. It returns 1 if the page is in the page table, and 0 if it is not.

removeOldest: O(1) time
This function simply removes the oldest page in the page table, by first changing the pointers to not point to the first page in the page table, and then freeing that memory.

addEnd: O(1) time
This function adds a new page to the end of the page table.

setReferene: O(N) time
This functin will loop through the page table to find the provded page table entry. It will then set this PTEs reference bit to 1.


secondChance Page Miss Rates

Page Table Size 10
Page Faults: 5075
Memory Accesses: 5120

Page Table Size 50
Page Faults: 4865
Memory Accesses: 5120

Page Table Size 100
Page Faults: 4592
Memory Accesses: 5120

Page Table Size 250
Page Faults: 3759
Memory Accesses: 5120

Page Table Size 500
Page Faults: 2617
Page Accesses: 5120


As we can see by the miss rates, secondChance is very similar to FIFO. However, secondChance is preferable due to the fairness of it when compared to FIFO.


Overall, these four algorithms are different in the way that they choose to replace pages. However, as shown by the page miss rates, it doens't have too much of an impact on how many page faults there are, due to the nature of the testfile.
If I were to choose a page replacement algorithm, I would say that LFU is probably the way to go, due to how much more fair it is.
