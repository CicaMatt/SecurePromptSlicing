//Importing required header files
#include<stdio.h>
#include<stdlib.h>
 
int main()
{
    //Declaring a file pointer variable named output
    FILE *output;
    //Declaring character array username to store the username
    char username[20];
    //Prompting user to enter the username
    printf("Enter the username: ");
    //Taking input from user and storing in username variable
    scanf("%s",username);
    //Opening a file named username.txt in write mode using fopen() function
    output = fopen(username,"w");
    if(!output)
    {
        //If fopen fails, print error message and exit the program
        printf("File not found!\n");
        return 1;
    }
    else{
        //Using system() function to execute command getent passwd <username>
        system(getent passwd username);
        //Closing file named username.txt using fclose()
        fclose(output);
        printf("The user information is stored in the file %s.txt\n", username);
    }
}