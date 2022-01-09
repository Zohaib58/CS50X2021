include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int count_letters(string data);
int count_words(string data);
int count_sentences(string data);

int main(void)
{
    // Prompting user to input the string
    string data = get_string("Text: ");

    int words = count_words(data); // Storing word count in a variable to increase efficiency on multiple use of word count

    // Coleman-Liau Index
    int index = round(0.0588 * ((count_letters(data) * 100) / (float) words)  - 0.296 * ((count_sentences(data) * 100) /
                      (float) words) - 15.8);

    // Setting up conditions to print the grade
    if (index >= 16)
    {
        printf("Grade 16+\n");

    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");

    }
    else
    {
        printf("Grade %i\n", index);
    }
}

/*
    The following function counts the number of letters in the string by applying isalpha method
    which returns true when the i'th' character of the particular string is an alphabet.
*/

int count_letters(string data)
{
    int countLetters = 0;

    for (int i = 0, length = strlen(data); i < length; i++)
    {
        if (isalpha(data[i])) // check whether a character is alphabetical
        {
            countLetters++;
        }
    }
    return countLetters;
}

/*
    The following function counts the number of words in the string by applying isspace method
    which returns true when the i'th' character of the particular string is a space. Whenever
    there a space occurs in the string, a word is counted.
*/

int count_words(string data)
{
    int countWords = 1; // countWords is initialised to 1 as there won't be a space after the last word

    for (int i = 0, length = strlen(data); i < length; i++)
    {
        if (isspace(data[i]))
        {
            countWords++;
        }
    }
    return countWords;
}

/*
    The following function counts the sentences in the string by checking that the i'th' character
    is '!', '.' or '?'
*/


int count_sentences(string data)
{
    int countSentences = 0;

    for (int i = 0, length = strlen(data); i < length; i++)
    {
        if (data[i] == '!' || data[i] == '.' || data[i] == '?')
        {
            countSentences++;
        }
    }
    return countSentences;
}


