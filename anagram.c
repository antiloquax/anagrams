#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "letsort.h"

#define MAXWORDLEN 100

int checkword(char *word);

int main()
{
    char word[MAXWORDLEN + 1];
    char temp[MAXWORDLEN + 1];
    char wordcpy[MAXWORDLEN + 1];
    char format[10];
    int len, i, found = 0;

    /* Variables for getline. */
    FILE *f;
    char *buf = NULL;
    size_t m = 0;

    /* Make a format string based on MAXWORDLEN. */
    sprintf(format, "%%%ds", MAXWORDLEN);
    printf("*** Anagram Solver ***\n\n");

    /* Get user's word. */
    printf("Enter your word: ");
    scanf(format, word);

    /* 
     * Change the word to lower case.
     * Check there are no invalid characters.
     */
    len = checkword(word);
    if (len == -1){
        printf("Invalid word.\n");
        exit(1);
    }

    /* Make a copy of the user's word and then sort the letters.*/
    strcpy(wordcpy, word);
    sortletters(word);

    /* Read through the file, looking for matches. */
    f = fopen("anag.txt", "r");
    while ((i = getline(&buf, &m, f)) != -1){

        /* Remove newline. */
        buf[--i] = '\0';

        /* Find mid-point, so we can index in to sorted string.*/
        i /= 2;
        if (i < 1)
            break;
        
        /* Check if sorted letters match user's letters. */
        if (!strcmp(word, &buf[i])){
            /* Make a new format string. */
            sprintf(format, "%%.%ds", i);
            /* Copy file word into temp. */
            sprintf(temp, format, buf);
            /* Print if different from original word. */
            if (strcmp(temp, wordcpy)){
                found = 1;
                printf("%s\n", temp);
            }
        }
    }
    if (!found)
        printf("No matches found.\n"); 
    
    fclose(f);
    free(buf);
    return 0;
}

/* Return length of word, or -1 on failure. */
int checkword(char *w)
{
    char *p, c;
    p = w;
    while (*p)
    {
        c = tolower(*p);
        if (c < 'a' || c > 'z')
            return -1;
        *p = c;
        p++;
    }
    return p-w;
}
