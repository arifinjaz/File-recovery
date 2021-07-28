#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t  BYTE; // New data type for 1 Byte

int main(int argc, char *argv[])
{

    if (argc < 2)
    {
        printf("Usage: ./recover image\n"); //Validation for a Valid entry
        return 1;
    }

    int i = 0; // Counter for File names.
    int found;
    char recovery[10] ;
    FILE *img = NULL;
    FILE *f = fopen(argv[1], "r"); // FIle open in read mode
    
    while (feof(f) != 1) // Execution start
    {
        BYTE *temp = malloc(512); // Memory allocation 
        if (temp == NULL) // Validation if pointer is NULL
        {
            printf("No Memory available.");
            return 2;
        }
        
        sprintf(recovery, "%03i.jpg", (i)); // Sprintf function to get name
        
        /*
            Below if condition will accomplish 2 tasks, 1) will read bytes into temp.
            2) It shall validate whe-ther its the last block,
        
        */
        
        if (fread(temp, 512, (sizeof(BYTE)), f) < 1) 
        {   
            fclose(img); // If Last block, close the last img.
        }

        if (temp[0] == 0xff && temp[1] == 0xd8 && temp[2] == 0xff 
            && (temp[3] & 0xf0) == 0xe0) // If condition to check whether a JPG starting.
        {
            if (found == 1) // Condition to check and close img.
            {
                fclose(img);
            }

            img = fopen(recovery, "a"); // Open new image in direct Apend mode.
            i++;
            found = 1;
        }

        if (found == 1)
        {
            fwrite(temp, (512), (sizeof(BYTE)), img); // to write bytes into the open img
            //free(temp);
        }
        free(temp);
    }

    //fclose(img);
    fclose(f);
    return 0;
}
