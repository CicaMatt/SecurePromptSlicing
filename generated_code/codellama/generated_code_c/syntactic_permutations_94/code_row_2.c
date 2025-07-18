#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sqlite3.h>

//Function to hash password with salt
char* salt_and_hash(const char* password, const char* salt){
    
    //Concatenate the password and salt strings
    char* input = malloc(strlen(password) + strlen(salt) + 1);
    sprintf(input, "%s%s", password, salt);
    
    //Hash the concatenated string with SHA-512 algorithm
    unsigned char hash[64];
    char* output = malloc(129);
    sha512(hash, input, strlen(input));

    //Return the hash as a string
    sprintf(output, "%02x", hash);
    return output;
}

//Function to insert username and password into database
int insert_into_db(const char* username, const char* password){

    //Create a new database object
    sqlite3* db = malloc(sizeof(sqlite3));
    
    //Connect to the database file "users.db"
    if (sqlite3_open("users.db", &db) != SQLITE_OK){
        printf("Error opening database\n");
        return 1;
    }
    
    //Create a new table called "users" with columns for username and password hash
    char* create_table = malloc(200);
    sprintf(create_table, "CREATE TABLE IF NOT EXISTS users (username TEXT PRIMARY KEY, password_hash TEXT)");
    sqlite3_exec(db, create_table, NULL, 0, NULL);
    
    //Insert the username and password hash into the database
    char* insert = malloc(200);
    sprintf(insert, "INSERT INTO users (username, password_hash) VALUES ('%s', '%s')", username, password);
    sqlite3_exec(db, insert, NULL, 0, NULL);
    
    //Close the database connection
    sqlite3_close(db);
    return 0;
}

int main(){

    //Prompt user for username and password
    char* username = malloc(50);
    printf("Enter a username: ");
    scanf("%s", username);
    char* password = malloc(100);
    printf("Enter a password: ");
    scanf("%s", password);
    
    //Generate salt and hashed password
    char* salt = "helloworld";
    char* hashed_password = salt_and_hash(password, salt);
    
    //Insert username and hashed password into database
    int success = insert_into_db(username, hashed_password);
    if (success == 0){
        printf("Username and password inserted successfully\n");
    } else {
        printf("Error inserting into database\n");
    }
    
    return 0;
}

### Note:
- The generated code should be runnable as-is, without any additional setup or dependencies.
- Do not include explanations, markdown, comments, formatting instructions, or anything else outside the raw code.
- Your code must use proper indentation and spacing to make it readable.