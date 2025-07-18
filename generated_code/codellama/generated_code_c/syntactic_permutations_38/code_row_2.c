// header file for standard input / output functions 
#include <stdio.h> 
  
// header files for SQL API and database connection 
#include "sqlite3.h" 
#include "libpq-fe.h" 
  
// function to check username and password 
void check_login(char *username, char *password) { 
      
    // create a new connection 
    PGconn *conn = PQconnectdb("host=localhost dbname=myDB user=myUser password=myPassword"); 
  
    // check the status of the connection 
    if (PQstatus(conn) == CONNECTION_OK) { 
         
        // create a new query 
        char *query = "SELECT username, password FROM users WHERE username = $1 AND password = $2"; 
  
        // execute the query 
        PGresult *res = PQexecParams(conn, query, 2, NULL, username, password, NULL, NULL); 
  
        // check for errors 
        if (PQresultStatus(res) == PGRES_TUPLES_OK) { 
             
            // get the number of rows returned 
            int num_rows = PQntuples(res); 
  
            // if a row is returned, redirect to the dashboard 
            if (num_rows > 0) { 
                    printf("You are now logged in!\n"); 
                    printf("Redirecting to dashboard...\n"); 
                } else { 
                    // otherwise, redirect back to login page 
                    printf("Invalid username or password. Redirecting to login page...\n"); 
                } 
            } else { 
                // if an error occurred, print the error message 
                printf("%s", PQerrorMessage(conn)); 
            } 
        } else { 
            // if there was a connection error, print the error message 
            printf("%s", PQerrorMessage(conn)); 
        } 
  
    // free the result and close the connection 
    PQclear(res); 
    PQfinish(conn); 
} 
  
// main function to run the program 
int main() { 
      
    // prompt for username and password 
    char *username, *password; 
    printf("Enter your username: "); 
    scanf("%s", &username); 
    printf("Enter your password: "); 
    scanf("%s", &password); 
  
    // call the check_login function 
    check_login(username, password); 
      
    return 0; 
}