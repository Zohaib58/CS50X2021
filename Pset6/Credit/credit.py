import cs50
from cs50 import get_int


def main():

    # Prompting user to take a positive input
    while (True):
        num = get_int("Enter the count:\n")
        if (num >= 0):
            break

    numForCardLength = num
    disp = num
    sumOfrem2 = 0
    cardLength = 0
    sumOfrem1 = 0  # The remainder of 1st, 3rd, 5th, ... digit when divided by 10 need
    # to be added AS-IS

    # Calculating checksum
    while (num > 0):

        sumOfrem1 += num % 10
        num = (int)(num / 10)

        rem2 = 0
        rem2 = (int)(num % 10)
        num = (int)(num / 10)

        """
         If the remainder of 2nd, 4th, 6th ... digits is greater or equal to 10 when multiplied by 2
         then that product needs to be broken down into two digits and need to be added separately

         For example, 12 would broken down into 1 and 2 and their addition would be 3 stored in
         the variable sumOfrem2
        """

        prodOfrem2 = 0
        prodOfrem2 = rem2 * 2
        if prodOfrem2 >= 10:
            sumOfrem2 += (int)(prodOfrem2 % 10)
            sumOfrem2 += (int)(prodOfrem2 / 10)
        else:
            sumOfrem2 += prodOfrem2

    totalOfrem1rem2 = sumOfrem1 + sumOfrem2

    # Checking if checksum is valid or not by applying Luhn's algorithm
    if (totalOfrem1rem2 % 10 == 0):
        status = True
    else:
        status = False

    # Credit-Card number length calculation
    while (numForCardLength > 0):
        numForCardLength = (int)(numForCardLength / 10)
        cardLength += 1

    # Determining the Card Type
    cardType = ""
    digits13 = 1000000000000
    digits15 = 10000000000000
    digits16 = 100000000000000
    digits162 = 1000000000000000

    if (cardLength == 15 and (((int)(disp / digits15)) == 34 or (((int)(disp / digits15)) == 37))):
        cardType = "AMEX"
    elif (cardLength == 16 and (((int)(disp / digits16)) >= 51 and (((int)(disp / digits16)) <= 55))):
        cardType = "MASTERCARD"
    elif ((cardLength == 16 and ((int)(disp / digits162)) == 4) or (cardLength == 13 and ((int)(disp / digits13)) == 4)):
        cardType = "VISA"
    else:
        status = False

    # If the checksum and CardType is valid display the CardType, otherwise display Invalid
    if (status == False):
        print("INVALID")
    else:
        print(cardType)

main()
