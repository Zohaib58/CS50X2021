// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file
    uint8_t header[HEADER_SIZE]; // Declaring an array of size HEADER_SIZE (44) of which each index stores 8 bits, specified by the type uint8_t
    fread(&header, HEADER_SIZE, 1, input); // Reading 44 bytes of information from the file pointer 'input' & storing it in the array 'header'
    fwrite(&header, HEADER_SIZE, 1, output); // Writing 44 bytes of information to the file pointer 'output' from the array 'header'

    // TODO: Read samples from input file and write updated data to output file
    int16_t buffer; // Declaring a variable 'buffer' which stores 16 bits, specified by the type int16_t
    while (fread(&buffer, sizeof(buffer), 1, input)) // Until the file runs out of content, read 16 bits (2 bytes) of information from the file input
    {
        buffer *= factor;
        fwrite(&buffer, sizeof(buffer), 1, output); // Each time content is read from the file input & stored in the variable buffer; same amount of  information needs to be written in the file 'output'
    }

    // Close files
    fclose(input);
    fclose(output);
}
