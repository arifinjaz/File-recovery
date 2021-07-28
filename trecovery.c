#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t  BYTE;
bool isfull (BYTE buffer[512]);
int isfulla (BYTE buffer[512]);
int main(int argc, char *argv[])
{

    if (argc < 1)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    //FILE *f = fopen(argv[1],"r");
    FILE *f = fopen("card.raw","r");


    int i = 0;
    int found;
    char recovery[10] ;
    FILE *img = NULL;

    while (feof(f) != 1)
    {
        BYTE* temp = calloc(512,1);

        if(temp == NULL)
        {
            return 2;
        }

        sprintf(recovery, "%03i.jpg", (i));
        fread(temp,(sizeof(BYTE)),512,f);

        //if (isfulla(temp) > 1)
        //{
            printf("Number:%i\n",isfulla(temp));
        //}

        //if (isfull(temp) == 1)
       // {
            //fclose(img);
           // fclose(f);
            //return 0;
       // }


        //printf("No of array filled: %i\n",c);
        //printf("1 filep:%ld\n",ftell(temp));

        if(temp[0] == 0xff && temp[1] == 0xd8 && temp[2] == 0xff && (temp[3] & 0xf0) == 0xe0)
        {
            if(found == 1)
            {
                fclose(img);
            }

            img = fopen (recovery,"a");
            i++;
            found = 1;
        }

        if(found == 1)
        {
            fwrite(temp,(sizeof(BYTE)),(512),img);
            free(temp);
        }

    }
    //free(temp);
    fclose(img);
    fclose(f);
    return 0;
}

bool isfull (BYTE buffer[512])
{
    int j = 0;
    for(int i = 0; i < 512; i++)
    {
        if(buffer[i]>0)
        {
            j++;
        }
    }

    if(j < 490)
    {
        return 1;
    }
    return 0;
}

int isfulla (BYTE buffer[512])
{
    int j = 0;
    for(int i = 0; i < 512; i++)
    {
        if(buffer[i]>0)
        {
            j++;
        }
    }

    if(j < 490)
    {
        return j;
    }
    return 0;
}