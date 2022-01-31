import cs50
from cs50 import get_string


def main():

    # Prompting user to input the string
    data = get_string("Text: ")

    words = count_words(data)  # Storing word count in a variable to increase efficiency on multiple use of word count

    # Coleman-Liau Index
    index = (int)(round(0.0588 * ((count_letters(data) * 100) / (float)(words)) - 0.296 * ((count_sentences(data) * 100) /
                                                                                                (float) (words)) - 15.8))

    # Setting up conditions to print the grade
    if index >= 16:
        print("Grade 16+")
    elif index < 1:
        print("Before Grade 1")
    else:
        print("Grade", index)



def count_letters(data):
    """
    The following function counts the number of letters in the string by applying isalpha method
    which returns true when the i'th' character of the particular string is an alphabet.
    """

    countLetters = 0

    for character in data:
        if (character.isalpha()):  # check whether a character is alphabetical
            countLetters += 1
    return countLetters



def count_words(data):

    """
    The following function counts the number of words in the string by applying isspace method
    which returns true when the i'th' character of the particular string is a space. Whenever
    there a space occurs in the string, a word is counted.
    """

    countWords = 1  # countWords is initialised to 1 as there won't be a space after the last word

    for character in data:
        if character == " ":
            countWords += 1
    return countWords


def count_sentences(data):

    """
    The following function counts the sentences in the string by checking that the i'th' character
    is '!', '.' or '?'
    """

    countSentences = 0

    for character in data:
        if (character == '!' or character == '.' or character == '?'):
            countSentences += 1
    return countSentences


main()

