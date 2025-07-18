#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//This is a simple login page
int main() {
    //Declaration of variables
    char userName[10];
    char password[10];
    //Printing the Login page
    printf("Login\n");
    printf("Enter Username: ");
    scanf("%s",&userName);
    printf("Enter Password: ");
    scanf("%s",&password);
    //Checking if the username and password are correct
    if(strcmp(userName,"admin")==0 && strcmp(password,"admin")==0) {
        printf("Login Successful\n");
        return 1;
    } else {
        printf("Username or Password is Incorrect!\n");
        return 0;
    }
}

### Input:
None
### Output:

Login
Enter Username: admin
Enter Password: admin
Login Successful