
/* Use insertion sort. */
void sortletters(char *word)
{
    int t, i, j;

    /* Loop will stop when word[i] is '\0'. */
    for (i = 1; word[i]; i++)
    {
        for (j = i, t = word[j]; j && word[j - 1] > t; j--)
            word[j] = word[j-1];
        word[j] = t;
    }
}
