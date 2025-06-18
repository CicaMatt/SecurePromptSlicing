#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

// Function to connect to db server and insert a user's username and password into the database
void insertUser(MYSQL *connection, char* username, char* password) {
    // Hash the password before storing it in the db
    char hashedPassword[256];
    strcpy(hashedPassword, crypt(password));
    printf("Inserting user %s with password %s\n", username, hashedPassword);
    
    if (mysql_query(connection, "INSERT INTO users VALUES ('username', 'hashedPassword')")) {
        fprintf(stderr, "%s\n", mysql_error(connection));
    }
}

// Function to authenticate a user by taking the username and password from the user. If the user is found in the database, 
// and the password matches, return true, otherwise false
bool authenticateUser(MYSQL *connection, char* username, char* password) {
    // Hash the provided password
    char hashedPassword[256];
    strcpy(hashedPassword, crypt(password));
    
    MYSQL_ROW row;
    if (mysql_query(connection, "SELECT * FROM users WHERE username = 'username' AND password = 'hashedPassword'")) {
        fprintf(stderr, "%s\n", mysql_error(connection));
        return false;
    }
    
    MYSQL_RES *result = mysql_store_result(connection);
    row = mysql_fetch_row(result);
    
    // If a user with the provided username and password is found in the db, authenticate them
    if (row != NULL) {
        return true;
    } else {
        return false;
    }
}

int main() {
    MYSQL *connection = mysql_init(NULL);
    
    // Connect to database server
    if (!mysql_real_connect(connection, "localhost", "root", "", "userdb", 3306, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(connection));
        return 1;
    }
    
    // Insert a user into the database
    insertUser(connection, "JohnDoe", "password");
    
    // Authenticate a user by taking the username and password from the user. If the user is found in the database, 
    // and the password matches, return true, otherwise false
    bool authenticated = authenticateUser(connection, "JaneDoe", "password123");
    
    // Close db connection
    mysql_close(connection);
    return 0;
}