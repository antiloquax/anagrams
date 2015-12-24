#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "letsort.h"

/* 
 * Reads in the dictionary of words.
 * Makes a new file with a word and the letter-sorted word 
 * on each line.
 */

int main()
{
    FILE *f = fopen("dictionary.txt", "r");
    FILE *g = fopen("anag.txt", "w");
    assert(f != NULL);
    assert(g != NULL);
    
    /* Read in the lines. */
    char *buf = NULL;
    size_t m = 0;
    int i;

    while ((i = getline(&buf, &m, f)) != -1){
        /* Remove newline character. */
        buf[i-1] = '\0'; 
        fprintf(g, "%s", buf);
        sortletters(buf);
        fprintf(g,"%s\n", buf);
    }
    fclose(f);
    fclose(g);
    return 0;
}


