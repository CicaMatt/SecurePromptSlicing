#include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    int main() {
        char* secret_info = "This is a super secret message";
        FILE *fptr;
        fptr = fopen("secret_file", "w"); // create file and open it in write mode
        fputs(secret_info, fptr);  // write the string to the file
        fclose(fptr); // close the file
        system("chmod 700 secret_file"); // change permissions of file to only owner can read, write and execute
        printf("File name: %s", "secret_file"); // print the name of the file to the screen
        return 0;
    }