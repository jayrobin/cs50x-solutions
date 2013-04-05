#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    if(argc != 2)
    {
        printf("Not enough args\n");
        return 1;
    }
    
    string keyword = argv[1];
    int klen = strlen(keyword);
    int k[klen];
    int ki;
    
    for(int i = 0; i < klen; i++)
    {
        ki = keyword[i];
        if(ki >= 65 && ki <= 90)
        {
            k[i] = ki - 65;
        }
        else if(ki >= 97 && ki <= 122)
        {
            k[i] = ki - 97;
        }
        else 
        {
            printf("Found non-alpha characters\n");
            return 1;
        }
    }
    
    string m;
    do
    {
        m = GetString();
    }
    while (strlen(m) == 0);
    
    char p;
    int c;
    int offset;
    ki = 0;
    for(int i = 0, len = strlen(m); i < len; i++)
    {
        p = m[i];
        if (p >= 65 && p <= 90) 
        {
            offset = 65;
        }
        else if (p >= 97 && p <= 122)
        {
        	offset = 97;
        }
        else
        {
            offset = 0;
        }
        
        if(offset > 0)
        {
            c = (((p - offset) + k[ki]) % 26) + offset;
            ki = (ki + 1) % klen;
        }
        else
        {
            c = p;
        }
        printf("%c", c);
    }
    
    printf("\n");
    
    
    return 0;
}