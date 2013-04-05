/****************************************************************************
 * Puff.c
 *
 * Computer Science 50
 * Problem Set 6
 *
 * 
 ***************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "forest.h"
#include "huffile.h"
#include "tree.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 3)
    {
        printf("Usage: infile outfile\n");
        return 1;
    }
    
    char* infile = argv[1];
    char* outfile = argv[2];

    // open input file 
    Huffile* inptr = hfopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 1;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        hfclose(inptr);
        printf("Could not create %s.\n", outfile);
        return 1;
    }
    
    // read file header
    Huffeader header;
    if(!hread(&header, inptr))
    {
        hfclose(inptr);
        fclose(outptr);
        printf("Infile is not huffed.\n");
        return 1;
    }
    
    // check header magic number against Huffile magic number
    if(header.magic != MAGIC)
    {
        hfclose(inptr);
        fclose(outptr);
        printf("Infile is not huffed.\n");
        return 1;
    }
    
    Forest* forest = mkforest();
    
    // calculate the valid checksum (sum of the frequencies)
    // simultaneously, plant the forest (create a node for each non-zero element)
    int validChecksum = 0;
    for(int i = 0, size = sizeof(header.frequencies) / sizeof(int); i < size; i++)
    {
        if(header.frequencies[i] > 0)
        {
            validChecksum += header.frequencies[i];
            
            Tree* tree = mktree();
            tree->symbol = i;
            tree->frequency = header.frequencies[i];
            tree->left = NULL;
            tree->right = NULL;
            plant(forest, tree);
        }
    }
    
    // check the calculated checksum against the header checksum
    if(header.checksum != validChecksum || header.checksum == 0)
    {
        hfclose(inptr);
        fclose(outptr);
        printf("Infile is not huffed.\n");
        return 1;
    }
    
    // create the Huffman tree by picking the two smallest trees and combining,
    // then replanting until only one node remains (the root)
    Tree* leftTree;
    Tree* rightTree;
    Tree* parentTree;
    bool rootFound = false;
    while(!rootFound)
    {
        leftTree = pick(forest);
        rightTree = pick(forest);
        
        if(rightTree)
        {
            parentTree = mktree();
            parentTree->frequency = leftTree->frequency + rightTree->frequency;
            parentTree->left = leftTree;
            parentTree->right = rightTree;
            
            plant(forest, parentTree);
        }
        else
        {
            // no rightTree, therefore node remaining is the root
            parentTree = leftTree;
            rootFound = true;
        }
    }
    
    // read the infile bit-by-bit, outputting the leaf nodes to the outfile as they
    // are found
    int c = 0;
    Tree* tree = parentTree;
    while(c >= 0)
    {
        c = bread(inptr);
        
		if(c == 0 && (tree->left))
		{
			tree = tree->left;
		}
		else if(c == 1)
		{
			tree = tree->right;
		}
		
		if(c>= 0 && (!tree->left || !tree->right))
		{
			fputc(tree->symbol, outptr);
			tree = parentTree;
		}
    }
    
    // close infile
    hfclose(inptr);

    // close outfile
    fclose(outptr);
    
    // burn the forest
    rmforest(forest);
    
    return 0;
}
