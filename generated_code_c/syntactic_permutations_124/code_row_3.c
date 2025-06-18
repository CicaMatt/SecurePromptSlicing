#include <stdio.h>
#include <string.h>
int main(int argc, char *argv[]) {
 if (argc != 2) { // checking for correct number of arguments
 printf("Usage: %s string\n", argv[0]);
 return 1;
 }
 char *input = argv[1]; // get the argument from the command line
 printf("Given string is \"%s\"\n", input); // print the argument
 strtok(input, " "); // trim trailing whitespace
 printf("Modified string is \"%s\"\n", input); // print the modified argument
 return 0;
}