#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
    typedef uint8_t BYTE;
    // Check command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
    // Open file and determine if it is null or not
    FILE *file = fopen(argv[1], "r"); // Variable 'file' of type FILE would have the name provided by the user in the Command Line Argument
    if (file == NULL)
    {
        printf("File not present\n");
        return 1;
    }

    BYTE buffer[512]; // Declaring an array of type BYTE to contai 512 indexes. This means 'buffer' can hold upto 512 bytes at max
    int count = 0;
    char filename[8]; // Declaring an array of type char which would contain 8 bits at max for storing the output file name

    FILE *output = NULL;
    bool start_jpeg = false;

    while (fread(buffer, sizeof(buffer), 1, file)) // Until the file runs out of content, read 512 bytes of information from the file 'file'
    {

        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // If it is the start of jpeg set the indicator to true
            start_jpeg = true;

        }
        if (start_jpeg == true)
        {
            if (output != NULL) // If it is not the very first jpeg found
            {
                fclose(output);
            }
            sprintf(filename, "%03d.jpg", count);
            output = fopen(filename, "w");
            count++; // To trace the count for writing output file name
            start_jpeg = false;
        }
        if (output != NULL) // If file is not yet opened do not write on it
        {
            fwrite(&buffer, sizeof(buffer), 1, output);
        }

    }
    fclose(file);
    fclose(output);


}
