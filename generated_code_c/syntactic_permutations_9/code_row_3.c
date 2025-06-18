#include <stdio.h> //header file for input/output library
    int main(int argc, char **argv) {//declaring variables and function
        int index = atoi(argv[1]);  //converting string to integer
        if (index <= 0 || index > argc - 2) { //checking for valid index value
            printf("Invalid Index");   //print error message
        } else {
            printf("%s", argv[index + 1]);// print argument from command line
        }
    }