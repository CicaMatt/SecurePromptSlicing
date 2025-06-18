//Importing header files

#include <stdio.h>
#include <stdlib.h>

//Defining unsubscribe function
void unsubscribe(char *email);

int main() 
{
    //Creating variable to hold email address
    char email[100];
    
    //Prompting user for email address
    printf("Enter Email Address: ");
    scanf("%s", email);
    
    //Passing email address into unsubscribe function
    unsubscribe(email);
    
    return 0;
}

void unsubscribe(char *email) {
    //Creating variables to hold database connection and query
    char* connection = "mysql_connect('localhost', 'root', '', 'newsletter')";
    char* query = "DELETE FROM subscribers WHERE email='%s'", email;
    
    //Connecting to database
    mysql_query(connection, query);
}