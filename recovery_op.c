#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <stdbool.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    FILE *ptr = fopen("card.raw", "r");

    if (ptr == NULL)
    {
        printf("Could not open the file\n");
        fclose(ptr);
        return 2;
    }

    // Creates a new file pointer, so that file is available to write throughout the loop. Set to NULL to avoid setting to garbage values
    FILE* file = NULL;
    // Creates an array of 512 bytes that can be used as buffer to read from the card file in 512 size blocks

    // Keeps track of how many jpgs have been created, so the name can be adapted for every one
    int x = 0;
    // Creates a string that will become the file name of the new jpg
    char *string = malloc(8);
    // Keeps track of whether a new jpg has been opened and blocks are just being added to it until the next jpg is found
    bool open = false;

    while (feof(ptr) == 0)
    {
        BYTE *array = malloc(512);
        if (array == NULL)
        {
            printf("Buffer does not have memory\n");
            return 3;
        }
        fread(array, 1, 512, ptr);

        if (feof(ptr) == 1)
        {
            break;
        }

        // Recognises whether beginning of sequence is a jpg
        if(array[0] == 0xff && array[1] == 0xd8 && array[2] == 0xff && (array[3] & 0xf0) == 0xe0)
        {
            if (!open)
            {
                // Gives signal that new jpg has been found and is ready to append
                open = true;
            }

            else
            {
                // Closes file if there was one already open and a new header has come up in the file
                fclose(file);
            }
            string[7] = '\0';
            sprintf(string, "%03i.jpg", x);
            file = fopen(string, "a");
            x++;
        }
        if (open)
        {
            fwrite(&array, 1, 512, file);
        }
        free(array);
    }

    fclose(ptr);
    fclose(file);
    free(string);
}