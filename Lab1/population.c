#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int startSize;
    do
    {
    startSize = get_int("Please enter initial number of animals: ");//1000
    }while (startSize < 9);

    // TODO: Prompt for end size
    int endSize;
    do
    {
    endSize = get_int("Please enter final number of animals: ");//2000
    }while (endSize < startSize);


    // TODO: Calculate number of years until we reach threshold
    int year = 0;
    while (startSize < endSize)
    {
    int born = startSize/3;
    int die = startSize/4;
    startSize = startSize + (born) - (die);
    year++;
    }


    // TODO: Print number of years
    printf("Years: %i\n", year);
}