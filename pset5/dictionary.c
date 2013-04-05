/****************************************************************************
 * James Robinson
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "dictionary.h"

#define ALPHABET_SIZE   26
#define ASCII_OFFSET    97
#define MAX_WORD_SIZE   45

typedef struct node
{
    struct node* alphabet[ALPHABET_SIZE + 1];   // 26 letters + apostrophe
    bool exists;    // defines whether a word exists at this point in the trie
}
node;

unsigned int dictionarySize = 0;     // tracks the number of entries in the dictionary
struct node* first = NULL;  // root node

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    node* nextNode = first;
    unsigned int c;
    unsigned int i = 0;
    
    while(c != '\0')
    {
        c = word[i];
        
        // switch to lowercase
        if(c <= 90 && c >= 65) {
            c |= 32;
        }
        
        // as in speller.c, only allow alpha or apostrophe
        if((c >= 97 && c <= 122) || (c == '\''))
        {
            // apostrophe is placed at the end of the alphabet
            if(c == '\'')
                c = ALPHABET_SIZE + ASCII_OFFSET;
                
            if(nextNode->alphabet[c - ASCII_OFFSET] == NULL)
            {
                return false;
            }
            else
            {
                nextNode = nextNode->alphabet[c - ASCII_OFFSET];
            }
        }
        
        i++;
    }
    
    return nextNode->exists;
}

node* createNode(void)
{
    return (node*) malloc(sizeof(node));
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // open input file
    FILE* dictionaryFile = fopen(dictionary, "r");
    if (dictionaryFile == NULL)
    {
        printf("Could not open file.\n");
        return false;
    }
    first = createNode();
    
    unsigned int c = 0;
    node* nextNode = first;
    
    while(c != EOF)
    {
        c = fgetc(dictionaryFile);
        if(c != '\n' && c != EOF)
        {
            if(c == '\'')
                c = ALPHABET_SIZE + ASCII_OFFSET;
                
            if(nextNode->alphabet[c - ASCII_OFFSET] == NULL)
            {
                nextNode->alphabet[c - ASCII_OFFSET] = createNode();
            }
            nextNode = nextNode->alphabet[c - ASCII_OFFSET];
        }
        // newline: set this node to an 'existing' word and move
        // back to the first node
        else if(c == '\n')
        {
            nextNode->exists = true;
            dictionarySize++;
            nextNode = first;
        }
    }
    
    
    fclose(dictionaryFile);
    
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return dictionarySize;
}

/**
 * Frees the memory used by this node and all nodes within it's alphabet
 */
void unloadNode(node* nextNode)
{
    // call unloadNode on every node in this node's alphabet
    for(int i = 0; i < ALPHABET_SIZE; i++)
    {
        if(nextNode->alphabet[i] != NULL)
        {
            unloadNode(nextNode->alphabet[i]);
        }
    }
    
    // once the alphabet nodes are freed, free this node
    free(nextNode);
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // call the recursive algorithm 'unloadNode', starting with the root
    unloadNode(first);
    return true;
}
