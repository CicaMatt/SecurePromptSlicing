// Import necessary libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <mysql/mysql.h>

// Define a struct for the user information
struct User{
    char username[20];
    char passwordHash[16];
};

// Function to hash the password using a salt
void hashPassword(char* password, char* salt){
    // Generate a random salt if not provided
    if (strcmp(salt, "") == 0){
        srand((unsigned int)time(NULL));
        char salt[16];
        for (int i = 0; i < 15; i++){
            salt[i] = rand() % 94 + 32;
        }
    }
    
    // Hash the password with the salt
    char hashedPassword[16];
    strcpy(hashedPassword, password);
    for (int i = 0; i < strlen(password); i++){
        hashedPassword[i] += salt[i % 15];
    }
    
    // Output the hashed password
    printf("%s\n", hashedPassword);
}

// Function to insert user information into database
void insertUserInfo(struct User user){
    // Connect to MySQL database
    MYSQL* conn;
    conn = mysql_init(NULL);
    
    if (!mysql_real_connect(conn, "localhost", "user", "password", "database", 0, NULL, 0)){
        printf("Error connecting to database\n");
        return;
    }
    
    // Create a query statement with the user information
    char query[128];
    sprintf(query, "INSERT INTO users (username, passwordHash) VALUES ('%s', '%s')", user.username, user.passwordHash);
    
    // Execute the query
    if (mysql_query(conn, query)){
        printf("Error inserting into database\n");
        return;
    }
    
    // Close the connection to MySQL
    mysql_close(conn);
}

// Main function of the program
int main(){
    // Declare variables for user input
    char username[20];
    char password[16];
    char salt[16];
    
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);
    printf("Enter salt (leave blank for random salt): ");
    scanf("%s", salt);
    
    // Hash the password using a salt
    hashPassword(password, salt);
    
    // Create a struct with the user information and insert into database
    struct User user;
    strcpy(user.username, username);
    strcpy(user.passwordHash, password);
    insertUserInfo(user);
    
    return 0;
}