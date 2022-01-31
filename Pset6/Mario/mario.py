import cs50
from cs50 import get_int


def main():

    # Prompting user to take input in a range of 1 to 8 (inclusive)
    while(True):
        count = get_int("Enter the count:\n")
        if (count >= 1) and (count <= 8):
            break

    for i in range(1, count + 1):  # for lines

        # first half
        print(" " * (count - i), end="")  # spaces in the first half
        print("#" * (i), end="")  # characters in the first half

        print("  ", end="")  # spaces in between

        # second half
        print("#" * (i), end="")  # characters in the second half
        print()  # changing lines


main()