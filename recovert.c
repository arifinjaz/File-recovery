#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#define size_of_block 512

typedef char *string;
typedef uint8_t BYTE;

int main(int argc, string argv[])
{
    if(argc != 2)
    {
        printf("please write name of the following memory card with the data type\n");
        return 1;
    }

    string fna = argv[1];

    FILE *raw = fopen(fna, "r");

    if(raw == NULL)
    {
        return 1;
    }

    BYTE jp[size_of_block];
    size_t read;

    int count = 0;
    char file_name[4];
    bool fnd = false;
    FILE *nimg;


   while(!feof(raw))
   {

       read = fread(jp, sizeof(BYTE), 512, raw);

       if(read == 0)
       {
           break;
       }

       if(jp[0] == 0xff && jp[1] == 0xd8 && jp[2] == 0xff && (jp[3] & 0xf0) == 0xe0)
       {
           fnd = true;
           if(count == 0)
           {
               count = 0;
           }


          else
          {
              fclose(nimg);
          }


           sprintf(file_name, "%03i.jpg", count++);
           nimg = fopen(file_name, "w");
           fwrite(jp, sizeof(BYTE), read, nimg);
       }


       else

       if(fnd)
       {
           fwrite(jp, sizeof(BYTE), read, nimg);
       }

   }
   fclose(raw);
   fclose(nimg);
}