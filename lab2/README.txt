Sam Burns
COEN 177L
F 2:15
Lab 2 ReadMe

The first task of this lab was to modify the minix sourcode so that upon booting up minix, it displays a message directly after the copyright message. This was found in the main.c file for the kernel, and I simply added a printf statement directly after the copyright. This had very little/no effect on the boot process of minix. 

The code for this modification is found in the main.c file.

For the second task of this lab, the goal was to modify MINIX's kernel by changing the way it schedules processes. Currently, MINIX uses a simple priority round robin algorithm to check each of the scheduling queues for ready processes. The are a total of 16 queues, and if the for loop in the pick_proc function selects an empty queue, the process that is selected is then determined by the random_process function, which essentially uses a random number generator based off the lower 32 bit word of value returned by read_tsc_64 as its pseudorandom value. 

However, the code that I modified was in the pick_proc function. Essentially, my mindset going into it, was to try and introduce a way for the scheduler to have a 10% chance to pick a lower level process. I generate a random value between 4 and 16, and using that value, I make it so the scheduler has a 10% chance to pick that queue to choose a process out of. I didn't include queues 0-3 since those ones were specified by the lab not to be modified since they contain the highest level priority processes.

When I first began testing my implentation of this logic, it had no effect on the boot time. It wasn't until I changed the value of q (which scheduling queue to pick a proccess out of) to equal the  value of a (my random value to determine which lower level queue to use) that it had an effect on the boot time. After making these modifications, the boot time for my VM was anywhere between  4-7 minutes.

What this essentially showed was that by introducing a chance of picking a lower level process, it made it so the higher level processes aren't executed every single time. Thus, the important processes necessary for booting up minix were not always chosen, so it made the boot time much longer.

The code that I modified in pick_proc is located on lines 1311-1316 and 1325-1333 in the proc.c file.


