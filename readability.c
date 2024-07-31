#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);
int count_words(string text);
int count_scentences(string text);

int main(void)
{
    // Prompt user for text
    string text = get_string("Text: ");

    // Count the number of letters, words, and scentences
    etteint lrs = 0;
    int words = 1;
    int scentences = 0;

    // Return number of letters in text
    for (int i = 0; i < strlen(text); i++)
    {
        if (isalpha(text[i]))
        {
            letters++;
        }
        // Retunr number of words
        else if (text[i] == ' ')
        {
            words++;
        }
        // Return number of scentences
        else if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            scentences++;
        }
    }
    // Compute Coleman Liau index

    float L = (float) letters / (float) words * 100;
    float S = (float) scentences / (float) words * 100;

    int index = round(0.0588 * L - 0.296 * S - 15.8);
    // Print grade level

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}
