#include <stdio.h>  // header file for input and output
#include <stdlib.h> // header file for standard library
#include <string.h> // header file for string manipulation
int main()
{
    char name[100]; // declaring a character array to store the name of the user
    printf("Enter your name: "); // asking for input from the user
    scanf("%s",name);  // scanning the input from the user and storing it in the name variable
    
    int age;  // declaring an integer variable to store the age of the user
    printf("Enter your age: "); // asking for input from the user
    scanf("%d",&age); // scanning the input from the user and storing it in the age variable
    
    char gender[10]; // declaring a character array to store the gender of the user
    printf("Enter your gender (M/F): "); // asking for input from the user
    scanf("%s",gender);  // scanning the input from the user and storing it in the name variable
    
    char email[100]; // declaring a character array to store the email of the user
    printf("Enter your email address: "); // asking for input from the user
    scanf("%s",email);  // scanning the input from the user and storing it in the name variable
    
    char password[100]; // declaring a character array to store the password of the user
    printf("Enter your password: "); // asking for input from the user
    scanf("%s",password);  // scanning the input from the user and storing it in the name variable
    
    FILE *fp; // creating a file pointer variable
    fp = fopen("users.txt","a"); // opening the users.txt file in appending mode
    if(fp == NULL) // checking for any errors while opening the file
    {
        printf("Error in opening the file\n"); // printing an error message if any error occurs
        exit(0);  // exiting the program
    }
    
    fprintf(fp,"%s %d %s %s %s\n",name,age,gender,email,password);  // writing the input data to the file in the format specified
    fclose(fp); // closing the file
    return 0;
}