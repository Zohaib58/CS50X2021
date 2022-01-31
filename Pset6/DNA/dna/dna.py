import cs50
import csv
import sys
import random


def main():
    # Ensure correct usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python database.csv sequences.txt")

    # Read content of DNA CSV File into memory as a dictionary
    file = open(sys.argv[1], "r");
    reader = csv.DictReader(file)
    #dict_reader = list(reader)
    # Read content of sequences.txt into memory as a string
    file = open(sys.argv[2], "r");
    txtfile = file.readline()


    print(calc(reader, txtfile))

def calc(reader, txtfile):
    length = len(reader.fieldnames)  # Calculating the length of field names to loop in future and store the data from database
    STRs = []  # List to store STRs

    # Traversing fieldnames in the obSTRect reader to store STRs in the list from the database
    for i in range(1, length):
        STRs.append(reader.fieldnames[i])



    # Calculating STR counts in the sequence text file
    data = {}

    list = STRs[:]  # To traverse over STRs list
    # Calculating occurrences of STRs in the txtfile and storing them in the dictionary as a value with key being t he STR itself
    for STR in list:
        count = 0
        maxCount = 0
        for i in range(0, len(txtfile)):
            while (txtfile[i : i+len(STR)] == STR):
                count += 1
                i += len(STR)
            i += len(STR)

            if count > maxCount:
                maxCount = count
            count = 0
        data[STR] = int(maxCount)


    # Comparing data dict with reader obj to find the matching person
    #print(data)

    for word in reader:
        counter = 0
        for char, count in word.items():
            if (char == "name"):
                name = count
            else:
                count = int(count)
                if count == data[char]:
                    counter += 1
                if counter == (len(data)):
                    return name
    return "No Match"

main()

