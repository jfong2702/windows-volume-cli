/*
* Arugments module header file
*/
#ifndef ARUGMENTS_HPP
#define ARUGMENTS_HPP

#include <stdbool.h>

#define BUFFER_SIZE 256 
#define QUERY "/q"
#define SET_VOL "/s"
#define ERROR 0
#define SUCCESS 1

/* Given a volume number string, sets the arg structure to coresponding value 
* Returns 1 on success,
* 0 on Failure
*/
int parseVolume(char* volumeString);

/* Prints the volume argument failure option */
void failVolume();

/* Do a volume level query */
void doQuery();

/* Prints the usage for the app. */
void printUsage();

/* Parses the arugments and sets the respective struct values. */
int parseArgs(char** argv, int argc);

typedef struct s_args
{
    bool query;
    bool set;
    float set_val;
} args_t;

extern args_t args;

#endif