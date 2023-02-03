#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
    //check that there is a file to read
    if(argv[1] == 0)
    {
        printf("Invalid usage.\n");
        return 1;
    }

    //open the file card.raw in this case
    FILE *infile = fopen(argv[1],"r");

    //create buffer to read into, buffer of 512 byte blocks
    typedef uint8_t BYTE;
    BYTE buffer[512];
    int BLOCK_SIZE = 512;

    FILE *outfile;

    int jpegfound = 0;
    bool first_jpeg = 1;
    char filename[8];

    //read the contents of card.raw
    while (fread(buffer, sizeof(BYTE), BLOCK_SIZE, infile) == 512)
    {
        //look for the jpeg signature
        if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (first_jpeg == 1)
            {

            //create memory to hold the string name of the file
            sprintf(filename, "%03i.jpg", jpegfound);

            //pass in the file pointer name to a new file for output
            outfile = fopen(filename,"w");

            //begin to write the file to the new one
            fwrite(buffer, sizeof(BYTE), 512, outfile);

            //keep track of which number jpeg you have found so you can use it as a dynamic file name
            jpegfound += 1;

            first_jpeg = 0;
            }
            else
            {
                fclose(outfile);

                //create memory to hold the string name of the file above
                sprintf(filename, "%03i.jpg", jpegfound);

                //pass in the file pointer name to a new file for output
                outfile = fopen(filename,"w");

                //begin to write the file to the new one
                fwrite(buffer, sizeof(BYTE), 512, outfile);

                jpegfound += 1;
            }
        }
        else if(first_jpeg == 0)
        {
        //continue to write the file to the new one
        fwrite(buffer, sizeof(BYTE), 512, outfile);
        }
    }

    fclose(outfile);
    fclose(infile);
}