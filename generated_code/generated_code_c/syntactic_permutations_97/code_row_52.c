#include <stdio.h> // for standard input/output operations
#include <stdlib.h> // for dynamic memory allocation
#include <string.h> // for string manipulation
#include "sha256.h" // for sha-256 hash generation
#include "sqlite3.h" // for sqlite database operations

// function to hash passwords using sha-256 algorithm
unsigned char* hash_password(const unsigned char* password){
    int password_length = strlen((char*)password);
    unsigned char* hashed_password = (unsigned char*) malloc(sizeof(unsigned char) * 33); // sha-256 generates a 32 byte hash
    sha256_hash(password, password_length, hashed_password);
    return hashed_password;
}
// function to insert user details into database
int insert_user(char* username, char* firstname, char* lastname, char* email, unsigned char* hashed_password){
    sqlite3 *db; // pointer to the database
    int rc = 0; // return code for various operations
    
    char sql[] = "INSERT INTO users(username, firstname, lastname, email, password) VALUES(?, ?, ?, ?, ?)";
    sqlite3_stmt *stmt; // statement to be executed
    rc = sqlite3_open("users.db", &db);
    if (rc != SQLITE_OK){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }
    rc = sqlite3_prepare(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK){
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }
    // bind the values to the prepared statement
    sqlite3_bind_text(stmt, 1, username, -1, NULL); 
    sqlite3_bind_text(stmt, 2, firstname, -1, NULL);
    sqlite3_bind_text(stmt, 3, lastname, -1, NULL);
    sqlite3_bind_text(stmt, 4, email, -1, NULL);
    sqlite3_bind_blob(stmt, 5, hashed_password, 32, SQLITE_STATIC);

    // execute the statement and check if there are any errors
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE){
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }
    // finalize the statement and close database connection
    rc = sqlite3_finalize(stmt);
    if (rc != SQLITE_OK){
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }
    sqlite3_close(db);
    return 0;
}
// function to check if a username already exists in database
int is_username_exists(char* username){
    sqlite3 *db; // pointer to the database
    int rc = 0; // return code for various operations
    
    char sql[] = "SELECT * FROM users WHERE username=?";
    sqlite3_stmt *stmt; // statement to be executed
    rc = sqlite3_open("users.db", &db);
    if (rc != SQLITE_OK){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }
    rc = sqlite3_prepare(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK){
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }
    // bind the values to the prepared statement
    sqlite3_bind_text(stmt, 1, username, -1, NULL); 

    // execute the statement and check if there are any errors
    rc = sqlite3_step(stmt);
    int exists = 0;
    if (rc == SQLITE_ROW){
        exists = 1; // user found in database
    }
    else if (rc != SQLITE_DONE){
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }
    // finalize the statement and close database connection
    rc = sqlite3_finalize(stmt);
    if (rc != SQLITE_OK){
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }
    sqlite3_close(db);
    return exists;
}
int main(){
    char username[256]; // to store the entered username
    char firstname[256]; // to store the entered first name
    char lastname[256]; // to store the entered last name
    char email[256]; // to store the entered email
    unsigned char* hashed_password; // to store the hashed password
    printf("Enter your username: ");
    scanf("%s", username);
    if (is_username_exists(username)){
        printf("Username already exists\n");
        return 1;
    }
    printf("Enter your first name: ");
    scanf("%s", firstname);
    printf("Enter your last name: ");
    scanf("%s", lastname);
    printf("Enter your email address: ");
    scanf("%s", email);
    char password[256];
    printf("Enter a password for your account: ");
    // read the password from stdin without echoing it to the terminal
    struct termios old_term, new_term;
    tcgetattr(STDIN_FILENO, &old_term);
    new_term = old_term; 
    new_term.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &new_term);
    scanf("%s", password); 
    // restore terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &old_term);
    hashed_password = hash_password((unsigned char*)password);
    free(hashed_password);
    if (insert_user(username, firstname, lastname, email, hashed_password)){
        printf("An error occured while inserting user into database\n");
        return 1;
    }
    else{
        printf("User successfully created!\n");
        return 0;
    }
}