#include <stdio.h>   // for standard I/O
#include <stdlib.h>  // for system()
#include <string.h>  // for string manipulation
int main() {
    FILE* fptr = fopen("file.txt", "w");  // create a file in write mode
    char message[] = "U2FsdGVkX1/R+WzJcxgvX/Iw==";  // the string to be written
    int len = strlen(message);  // get length of message
    fwrite(message, sizeof(char), len, fptr);  // write message to file
    system("chmod 0400 file.txt");  // change permissions
    char permissions[10];
    sprintf(permissions, "%o", 0400);  // convert octal value to string
    printf("The permissions of the file are: %s\n", permissions);  // print permissions
    return 0;  // end program
}