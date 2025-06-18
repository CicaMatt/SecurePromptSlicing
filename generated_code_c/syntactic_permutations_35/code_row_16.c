// Import required packages
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    
    // Define variables and functions
    #define MAX_BUFFER 256
    char username[MAX_BUFFER];
    char password[MAX_BUFFER];
    
    void login(char *username, char *password) {
        // Connect to database
        MYSQL *conn = mysql_init(NULL);
        if (mysql_real_connect(conn, "localhost", "root", "root", "login", 0, NULL, 0)) {
            printf("Connected...\n");
            
            // Prepare SQL statement
            char sql[MAX_BUFFER];
            sprintf(sql, "SELECT * FROM users WHERE username = '%s' AND password = '%s'", username, password);
            
            // Execute SQL statement
            MYSQL_RES *result = mysql_query(conn, sql);
            if (mysql_num_rows(result) > 0) {
                printf("Login successful...\n");
                
                // Redirect to home page
                char redirect[MAX_BUFFER];
                sprintf(redirect, "location:home.html");
                header(redirect);
            } else {
                printf("Login failed...\n");
                
                // Redirect to login page
                char redirect[MAX_BUFFER];
                sprintf(redirect, "location:login.html");
                header(redirect);
            }
        } else {
            printf("Connection failed...\n");
        }
    }
    
    int main() {
        // Get username and password from form data
        if (isset($_POST['username']) && isset($_POST['password'])) {
            strcpy(username, $_POST['username']);
            strcpy(password, $_POST['password']);
            
            // Call login function
            login(username, password);
        } else {
            printf("Invalid form data...\n");
        }
        
        return 0;
    }