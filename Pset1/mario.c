#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Prompting user to take input in a range of 1 to 8 (inclusivest)
    int count = 0;
    do
    {
        count = get_int("Enter the count:\n");
    }
    while (count < 1 || count > 8);


    int i = 0;
    int j = 0;

    for (i = 1; i <= count; i++) // for lines
    {
        // first half
        for (j = 1; j <= count - i; j++) // spaces in the first half
        {
            printf(" ");


        }
        for (int k = 0; k <= count - j; k++) // characters in the first half
        {
            printf("#");
        }


        printf("  "); // spaces in between



        // second half
        for (int k = 0; k <= count - j; k++) // characters in the second half
        {
            printf("#");
        }
        printf("\n"); // changing lines

    }
}
