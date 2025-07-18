#include <stdio.h> 
// a function that takes in command line argument and returns the value at the index provided as an array of strings
int main(int argc, char *argv[]) {
    // code to check the number of arguments entered by user
    if (argc == 2) {
        int index = atoi(argv[1]);
        return index;
    } else {
        printf("Error: Wrong number of command line argument.");
    }
}