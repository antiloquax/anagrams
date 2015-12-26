#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "letsort.h"

#define MAXWORDLEN 100
#define DICTIONARY "dictionary.txt"
#define ANAGRAMS "anag.txt"

int checkword(char *word);
int find(char *word);
int match(char *word);
int ismatch(char *pat, char *str);

int main()
{
    char word[MAXWORDLEN + 1];
    char format[10];
    int found;

    /* Make a format string based on MAXWORDLEN. */
    sprintf(format, "%%%ds", MAXWORDLEN);
    printf("*** Anagram Solver ***\n\n");

    printf("To find a word with missing letters instead,\n");
    printf("use a . to stand for the unknown letter(s).\n");

    while (1) {
        /* Get user's word. */
        printf("Enter your word (or use 'q' to quit): ");
        scanf(format, word);
        if (!strcmp(word, "q"))
                break;

        /* Reset counter. */ 
        found = 0;
        
        /* 
         * Change the word to lower case & check for invalid characters. 
         * Return value of checkword() tells us what to do next.
         */
        switch (checkword(word)) {
            /* -1 means we do nothing. */
            case -1:
                printf("Invalid word.\n");
                found = -1;
                break;
            /* Zero means we look for an anagram. */
            case 0:
                found = find(word);
                break;
            /* One means look for word with missing letters. */
            case 1:
                found = match(word);
                break;
            default:
                /* Shouldn't ever get here. */
                break;
        }
        if (!found)
            printf("No matches found.\n"); 
    }
    return 0;
}

/* Look for anagrams. Return number of matches found. */
int find(char *word)
{
    char wordcpy[MAXWORDLEN + 1];
    char temp[MAXWORDLEN + 1];
    char format[10];
    int i, found = 0;

    /* Variables for getline. */
    FILE *f;
    char *buf = NULL;
    size_t m = 0;

    /* Make a copy of the user's word and then sort the letters.*/
    strcpy(wordcpy, word);
    sortletters(word);

    /* Read through the file, looking for matches. */
    f = fopen(ANAGRAMS, "r");
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
    fclose(f);
    free(buf);
    return found;
}

int match(char *word)
{
    int i, found = 0; 
    int len = strlen(word);
    
    FILE *f;
    char *buf = NULL;
    size_t m = 0;

    f = fopen(DICTIONARY, "r");
    while ((i = getline(&buf, &m, f)) != -1){
        /* Remove newline. */
        buf[--i] = '\0';
        if (len != i)
            continue;
        
        /* Check this word against the pattern. */
        if (ismatch(word, buf)){
            found++;
            printf("%s\n", buf);
        }
    }

    fclose(f);
    free(buf);
    return found;
}

/* Check the pattern against the string. */
int ismatch(char *pat, char *str)
{
    while(*pat){
        if (*pat != *str && *pat != '.')
            return 0;
        *pat++;
        *str++;
    }

    return 1;
}

/* 
 * Change the string to lower case.
 * Return 0 if only letters found.
 * Ruturn 1 if '.' found.
 */
int checkword(char *w)
{
    int dot = 0;
    char c;
    while (*w)
    {
        c = tolower(*w);
        if (c == '.')
            dot = 1;
        else if (c < 'a' || c > 'z')
            return -1;
        *w = c;
        w++;
    }
    return dot;
}

