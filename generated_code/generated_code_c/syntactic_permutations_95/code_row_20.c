#include <stdio.h>  // for IO operations
#include <stdlib.h> // for dynamic memory allocation, process control etc.
#include <string.h> // for string operations

// Importing header files of MySQL and SHA256 libraries
#include "mysql/mysql.h" 
#include "sha256/sha256.h" 

// Defining the structure to store the hashed password and salt
typedef struct {
    char hashed_password[100];
    char salt[100];
} user;

// Function to generate random salt for each user
char* getSalt(int length) 
{
    // Initializing variables
    int i = 0;
    const char alphabet[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
    char* salt = (char*)malloc(length + 1);
    
    // Generating random salt
    for (i = 0; i < length; ++i) {
        int key = rand() % (int)(sizeof(alphabet) - 1);
        salt[i] = alphabet[key];
    }
    
    // Terminating the string
    salt[length] = '\0';
    
    return salt;
}

// Function to hash the password and store it in the structure along with the salt
user* getHash(char* password) 
{
    // Initializing variables
    user* u = (user*)malloc(sizeof(user));
    char* hashed_password = NULL;
    const EVP_MD *md = EVP_sha256();
    
    // Hashing the password using SHA-256
    unsigned int md_len = 0;
    EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
    hashed_password = (char*)malloc(SHA256_DIGEST_LENGTH);
    
    // Initializing the hashing algorithm
    EVP_DigestInit_ex(mdctx, md, NULL);
    
    // Hashing the password and storing it in the structure
    EVP_DigestUpdate(mdctx, password, strlen(password));
    EVP_DigestFinal_ex(mdctx, (unsigned char*)hashed_password, &md_len);
    
    // Generating random salt for each user and appending it to the hashed password
    u->salt = getSalt(10);
    strcat(hashed_password, u->salt);
    u->hashed_password = hashed_password;
    
    return u;
}

// Function to store the hashed password and salt in the database
void insertIntoDatabase(char* username, char* hashed_password) 
{
    // Initializing variables
    MYSQL *conn = mysql_init(NULL);
    const char* server = "localhost";
    const char* user = "root";
    const char* password = ""; /* set me first */
    const char* database = "users";
    
    // Connecting to the MySQL server and selecting the database
    conn = mysql_real_connect(conn, server, user, password, database, 0, NULL, 0);
    
    // Checking for successful connection
    if (conn) {
        printf("Connection Successful!\n");
        
        // Inserting the hashed password and salt into the database
        char* query = "INSERT INTO user_details VALUES(?, ?)";
        MYSQL_STMT *stmt = mysql_stmt_init(conn);
        if (mysql_stmt_prepare(stmt, query, strlen(query))) {
            printf("Error: %s\n", mysql_error(conn));
            exit(1);
        }
        
        // Binding the values to the parameters
        MYSQL_BIND params[2];
        memset(params, 0, sizeof(params));
        char buffer[256];
        strcpy(buffer, hashed_password);
        unsigned long length = strlen(hashed_password);
        
        params[0].buffer_type = MYSQL_TYPE_STRING;
        params[0].buffer = (char*)username;
        params[0].is_null = 0;
        params[0].length = &length;
        
        params[1].buffer_type = MYSQL_TYPE_STRING;
        params[1].buffer = buffer;
        params[1].is_null = 0;
        params[1].length = &length;
        
        // Inserting the values into the database
        mysql_stmt_bind_param(stmt, params);
        mysql_stmt_execute(stmt);
    } else {
        printf("Error: %s\n", mysql_error(conn));
    }
}

int main() 
{
    // Initializing variables
    char username[100];
    char password[100];
    
    // Getting the input from user
    printf("Enter Username: ");
    scanf("%s", &username);
    printf("Enter Password: ");
    scanf("%s", &password);
    
    // Generating hashed password and salt
    user* u = getHash(password);
    
    // Storing the hashed password and salt in the database
    insertIntoDatabase(username, u->hashed_password);
    
    return 0;
}