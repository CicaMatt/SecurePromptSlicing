#include <stdio.h>  // For printf() function
#include <stdlib.h>  // For exit() function
#include <string.h>  // For strcpy() and strcat() functions

int main(){
    char filename[100];  // To store the path and name of file
    char write_str[] = "U2FsdGVkX1/R+WzJcxgvX/Iw==";  // String to be written in the file

    printf("Enter the filename along with it's full path: ");
    scanf("%s", filename);  // To take input from user for filename and path

    FILE *fp = fopen(filename, "a");  // Opening the file in append mode
    if (fp == NULL){
        printf("Error opening file!\n");  // Error message to be displayed when file cannot be opened
        exit(1);  // To exit the program on error
    }
    fputs(write_str, fp);  // Writing string in the file
    fclose(fp);  // Closing the file

    printf("File created successfully!\n");  // Success message to be displayed after successful file creation
}