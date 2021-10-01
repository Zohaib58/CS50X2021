#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Prompting user to input the credit card number
    long num = 0;
    do
    {
     num = get_long("Enter the number: ");
    }
    while (num < 0);

    long numForCardLength = num;
    long disp = num;
    int sumOfrem2 = 0;
    int cardLength = 0;
    int sumOfrem1 = 0; //The remainder of 1st, 3rd, 5th, ... digit when divided by 10 need
                       // to be added AS-IS

    // Calculating checksum
    while (num > 0)
    {
        sumOfrem1 += num % 10;
        num /= 10;

        int rem2 = num % 10;
        num /= 10;

        /*
         If the remainder of 2nd, 4th, 6th ... digits is greater or equal to 10 when multiplied by 2
         then that product needs to be broken down into two digits and need to be added separately

         For example, 12 would broken down into 1 and 2 and their addition would be 3 stored in
         the variable sumOfrem2
        */

        int prodOfrem2 = rem2 * 2;
        if (prodOfrem2 >= 10)
        {
        sumOfrem2 += prodOfrem2 % 10;
        sumOfrem2 += prodOfrem2 / 10;
        }
        else
        {
        sumOfrem2 += prodOfrem2;
        }

    }
    int totalOfrem1rem2 = sumOfrem1 + sumOfrem2;

    // Checking if checksum is valid or not by applying Luhn's algorithm
    bool status;
    if (totalOfrem1rem2 % 10 == 0) status = true;
    else status = false;


    // Credit-Card number length calculation
    while (numForCardLength > 0)
    {
        numForCardLength /= 10;
        cardLength++;
    }

    // Determining the Card Type
    string cardType = "";
    const long digits13 = 1000000000000;
    const long digits15 = 10000000000000;
    const long digits16 = 100000000000000;
    const long digits162 = 1000000000000000;

    if (cardLength == 15 && (disp / digits15 == 34 || disp / digits15 == 37))
    {

        cardType = "AMEX";
    }

    else if (cardLength == 16 && (disp / digits16 >= 51 && disp / digits16 <= 55))
    {
        cardType = "MASTERCARD";
    }
    else if ((cardLength == 16  && disp / digits162 == 4) || (cardLength == 13 && disp / digits13 == 4))
    {
        cardType = "VISA";
    }
    else status = false;

    // If the checksum and CardType is valid display the CardType, otherwise display Invalid
    if (status == false) printf("INVALID\n");
    else printf("%s\n",cardType);
}
