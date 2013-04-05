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
    
    int k = atoi(argv[1]);
    k = k % 26;
    if(k < 0)
    {
        printf("Must be positive\n");
        return 1;
    }
    
    string m;
    do
    {
        m = GetString();
    }
    while (strlen(m) == 0);
    
    char p;
    int c;
    for(int i = 0, len = strlen(m); i < len; i++)
    {
        p = m[i];
        
        c = p + k;
        
        if((p >= 65 && p <= 90 && c > 90) || (p >= 97 && p <= 122 && c > 122))
        {
            c = p - (26 - k);
        	printf("%c", c);
        }
        else if ((p >= 65 && p <= 90) || (p >= 97 && p <= 122))
        {
        	printf("%c", c);
        }
        else 
        {
        	printf("%c", p);
        }
		
    }

	printf("\n");
    
    return 0;
}