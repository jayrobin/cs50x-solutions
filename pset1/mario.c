#include <stdio.h>
#include <cs50.h>

int main (void)
{
	int height;

    do
    {
        printf("Height: ");
        height = GetInt();
    } while (height < 0 || height > 23);
    
    for (int i = 1; i <= height; i++)
    {
    	for (int j = 0; j <= height; j++)
        {
            if (height - j <= i)
            {
             	printf("#"); 
            }
            else
            {  
                printf(" ");
            }
        }
        printf("\n");
    }
    
	return 0;
}
