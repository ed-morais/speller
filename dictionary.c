// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

//Word counter
unsigned int counter = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    //Hash word to obtain hash value
    int head = hash(word);
    //Access linked list
    node *cursor = table[head];
    //Loop to go through the linked list
    while (cursor != NULL)
    {
        //Check if it is the same word
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        
        //Points cursor to next node
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    /* credits to u/delipity
     *https://www.reddit.com/r/cs50/comments/1x6vc8/pset6_trie_vs_hashtable/
     */
    unsigned int hash = 0;
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        hash = (hash << 2) ^ word[i];
    }
    return hash % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    //Declaring the buffer
    char buffer[46];
    
    //Open dictionary file
    FILE *dictPtr = fopen(dictionary, "r");
    
    //Make sure DICTIONARY opened successfully 
    if (dictPtr == NULL)
    {
        printf("Unable to open file\n");
        return false;
    }
    
    //Read strings from file until the end of the file
    while (fscanf(dictPtr, "%s", buffer) != EOF)
    {
        //New node
        node *newnode = malloc(sizeof(node));
        if (newnode == NULL)
        {
            return false;
        }
        
        //Copy word into the buffer
        strcpy(newnode->word, buffer);
        newnode->next = NULL;
        
        //Use hash funcion to obtain hash value
        int head = hash(buffer);
        
        //New node
        newnode->next = table[head];
        
        //Set head to new node
        table[head] = newnode;
        
        //Update counter
        counter++;
    }
    fclose(dictPtr);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    //Checks if there is any word in dictionary
    if (counter > 0)
    {
        //Return the number of words in dictionary
        return counter;
    }
    else
    {
        return false;  
    }
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    //Loop through buckets
    for (int i = 0; i < 26; i++)
    {
        node *cursor = table[i];
        
        // Free cursor
        while (cursor != NULL)
        {
            //create buffer
            node *buffer = cursor;
            //move cursor to the next node
            cursor = cursor->next;
            //free buffer
            free(buffer);
        }
        //In case cursor == null
        if (i == 25)
        {
            if (cursor == NULL)
            {
                return true;
            }
        }
    }
    return false;
}
