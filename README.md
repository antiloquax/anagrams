Anagram program

This is a simple anagram solver.

First, I used a dictionary of British English word from the 12dict package.
Download location: http://wordlist.aspell.net/12dicts/

The preparedict program (which needs to be compiled with letsort.c), goes through each line in the file and sorts the letters in each word.
I used insertion sort for this task.
The file anag.txt contains each word on a line with its sorted version immediately after.

The anag program (which needs to be compiled with letsort.c also), asks the user for a string of letters. These are then sorted and compared against the sorted words in anag.txt.

If a match is found that is not the same as the user's input, it is displayed.

