/****************************************************************************
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 ***************************************************************************/
 
 #include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
 
// no need to include all bmp.h - only need BYTE
typedef uint8_t  BYTE;
 
#define BLOCKSIZE         512
 
int main(void)
{
    // open input file
    FILE* inptr = fopen("card.raw", "r");
    if (inptr == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }
               
    // calculate filesize
    // from http://stackoverflow.com/questions/238603/how-can-i-get-a-files-size-in-c
    //fseek(inptr, 0, SEEK_END);
    //int filesize = ftell(inptr);
   
    // reset position to start of file
    //fseek(inptr, 0, SEEK_SET);
   
    // point to output stream
    FILE* outptr = NULL;
               
    // initialise JPEG index and filename
    int jpegIndex = 0;
    char filename[8];
   
    // BYTE array size of a data block
    BYTE block[BLOCKSIZE];
   
    // boolean indicating whether or not a file is currently being written to
    int writingToFile = 0;
    //int index = 0;
    //int data = 0;
    
    // iterate until end of file reached
    //while(!feof(inptr))
    //{
        //printf("a %d\n", ftell(inptr));
        while(fread(block, sizeof(BYTE), BLOCKSIZE, inptr) > 0)
        {
           // printf("Pos: %d\n", index);
            /*data = 0;
            //check for empty slack space
            for(int i = 0; i < BLOCKSIZE; i++)
            {
                if(block[i] != 0x00)
                {
                    data++;
                }
            }
           
            if(data == 0)
            {
                printf("Closing file: empty space\n");
                writingToFile = 0;
                if(outptr != NULL)
                {
                    fclose(outptr);
                }
            }*/
                           
           
           
            // check for a JPEG signature
            if(block[0] == 0xff &&
                block[1] == 0xd8 &&
                block[2] == 0xff &&
                (block[3] == 0xe0 || block[3] == 0xe1))
            {
                //printf("Found JPEG %d\n", jpegIndex);
                if(writingToFile)
                {
                    //printf("Closing file\n");
                    fclose(outptr);
                }
               
                // open output file
                sprintf(filename, "%03d.jpg", jpegIndex);
                //printf("Creating file %03d.jpg\n", jpegIndex);
                outptr = fopen(filename, "w");
                if (outptr == NULL)
                {
                    printf("Could not create file.\n");
                    return 2;
                }
               
                jpegIndex++;
               
                writingToFile = 1;
            }
           
            if(writingToFile)
            {
                //printf("Writing block\n");
                // write block to file
                if(fwrite(block, sizeof(BYTE), BLOCKSIZE, outptr) == 0) {
                    printf("Error writing to file.\n");
                    return 3;
                }
            }
        //index++;
        }
        //printf("%d %d %d\n", index, feof(inptr), ftell(inptr));
                   
    //}

    // close file streams
    fclose(inptr);
    fclose(outptr);

    return 0;
}
