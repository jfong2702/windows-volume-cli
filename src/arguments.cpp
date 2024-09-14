#include "arguments.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

args_t args = {false, false, 0};


int parseArgs(char** argv, int argc)
{
    int i;
    if(argc < 2) printUsage();

    for(i = 1; i < argc; i++)
    {
        if(strcmp(argv[i], QUERY) == 0) doQuery();

        if(strcmp(argv[i], SET_VOL) == 0)
        {
            if(i == argc - 1) 
            {
                printUsage();
                return ERROR;
            }

            i++;
            if(parseVolume(argv[i]) == ERROR)
            {
                printUsage();
                return ERROR;
            }
        }
    }

    return SUCCESS;
}

int parseVolume(char* volumeString)
{
    errno = 0;
    char* end_ptr;
    unsigned val = strtoul(volumeString, &end_ptr, 0);
    if(errno != 0 || end_ptr == volumeString)
    {
        puts("Must enter valid volume number 0-100!\n");
        return ERROR;
    }
    if(val > 100)
    {
        failVolume();
        puts("Must enter valid volume number 0-100!\n");
        return ERROR;
    }
    args.set = true;
    args.set_val = val / 100.0f;
    return SUCCESS;
}

void failVolume()
{
    args.set = false;
    args.set_val = 0;
}

void doQuery()
{
    args.query = true;
}

void printUsage()
{
    puts("Windows command line volume control untility:\nUsage:\n");
    puts("volume [options]\n");
    puts("**************OPTIONS*****************\n");
    puts("/q -> query: queries the current volume for the device.\n");
    puts("/s [0-100] -> set: sets the volume to the given argument amount.\n\n");
}