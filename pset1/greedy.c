#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main (void)
{
	float owed;
    int owedInt;
    int coins = 0;

    do
    {
        printf("How much change is owed? ");
        owed = GetFloat();
    } while (owed <= 0);
    
    owedInt = round(owed * 100);
    
    while (owedInt > 0)
    {
        if (owedInt - 25 >= 0)
        {
            owedInt -= 25;
            coins++;
        }
        else if (owedInt - 10 >= 0)
        {
            owedInt -= 10;
            coins++;
        }
        else if (owedInt - 5 >= 0)
        {
            owedInt -= 5;
            coins++;
        }
        else
        {
            owedInt -= 1;
            coins++;
        }
    }
    
    printf("%d\n", coins);
    
    
	return 0;
}
