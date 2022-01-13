// Implements a dictionary's functionality

#include <stdbool.h>

#include <stdio.h> // change1
#include <string.h>
#include <strings.h> // change2
#include <stdlib.h> // chaneg3
#include <ctype.h> // change4

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// To check the number of words loaded in an array
int word_count = 0; // change4
// Number of buckets in hash table
const unsigned int N = 100000;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int hash_value = hash(word); // finding hash value of the word
    //bool found = false;

    node *currentPointer = table[hash_value]; // Assigning the node in the hash table with the same hash value to the newl
    // created pointer of type node

    /*
     The following code will run until the node currenPointer is empty.
     It compares the word stored in the node pointed by currentPointer with the word that this function check accepts as a parameter.
     The comparison is case insensitive (with the help of function strcasecmp) as per the requirement of the qs.
     If both the strings are same true is returned, otherwise the pointer 'currentPointer' is pointed to the next node.
    */


    while (currentPointer != NULL)
    {
        if (strcasecmp(currentPointer -> word,  word) == 0)
        {
            return true;
        }
        else
        {
            currentPointer = currentPointer -> next;

        }

    }
    return false; // No matching string found
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    // Got this hash function from https://cs50.stackexchange.com/questions/38753/cs50-good-hash-function-for-pset5-speller
    int hash = 5381;


    while (*word != '\0')
    {
        hash = ((hash << 4) + (int)(tolower(*word))) % N;
        word++;
    }

    return hash % N;

}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO

    // A file pointer used to handle the dictionary opened
    FILE *file = fopen(dictionary, "r");

    // If file doesn't open or doesn't exist return false
    if (file == NULL)
    {
        return false;
    }
    char word[LENGTH + 1];

    // Reads string from dict and places it into word until End of Dictionary is reached
    while (fscanf(file, "%s", word) != EOF)
    {
        // Allocate memory for new node
        node *n = malloc(sizeof(node));

        // If malloc fails to allocate memory, return false
        if (n == NULL)
        {
            return false;
        }

        strcpy(n->word, word); // char* strcpy(char* destination, const char* source);

        int hash_value = hash(word); // Getting hash value/index for the word

        /*
        To avoid the loss of other nodes; firstly, the pointer, to the node at current hash_value in the hash
        table, is stored in the next node of pointer 'n'. This is done because the pointer at current hash_value
        contains the link to the rest of the nodes, so by assigning it to the next node of 'n' the link is still maintained
        */
        n -> next = table[hash_value];
        table[hash_value] = n; // node n is stored in the hash table at index hash_value

        word_count++; // Every new word added increments this variable

    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return word_count; // returning the global variable that was incremented in the global function whenever
                       // a new word was added
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    int j = 0;
    // Emptying the nodes using a temporary variable
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];

        while (cursor)
        {
            node *tmp = cursor;
            cursor = cursor -> next;
            free(tmp);
        }
        j++;

    }
    if (j == N) // if all the nodes are emptied then return true otherwise false
    {
        return true;
    }
    return false;

}
