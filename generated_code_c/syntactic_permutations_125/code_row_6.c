#include <stdio.h>  //importing library for standard I/O operations.
#include <string.h> //importing library for string manipulation operations.
#define MAX_LENGTH 1024 //defining maximum length of the command line argument.
int main(int argc, char *argv[]) { //main function which takes in arguments and prints them out to the console.
        if (argc < 2) return 1; //checking that there is a command line argument present
        else {
            size_t len = strlen(argv[1]);//getting length of the command line argument.
            while (len > 0 && argv[1][len - 1] == ' ') --len; //trimming trailing whitespace characters from the argument.
            printf("%.*s", len, argv[1]); //printing out the trimmed string to the console.
        }
        return 0;
    }