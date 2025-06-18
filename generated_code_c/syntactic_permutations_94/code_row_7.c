#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/sha.h>

// Define structures for user credentials and salt
struct User {
    char username[32];
    unsigned char hashed_passwd[64];
};

struct Salt {
    unsigned char value[16];
};

// Declare functions to generate salt, hash password, and insert user credentials into database
void generateSalt(struct Salt *salt);
void hashPassword(const char *password, struct Salt *salt, unsigned char *hashed_passwd);
int insertUserCreds(const struct User *user);

// Declare main() function to prompt user for username and password, generate salt,
// hash password, and insert user credentials into database
int main()
{
    // Declare variables for username and password
    char username[32];
    char password[32];

    // Declare structures for user credentials and salt
    struct User user;
    struct Salt salt;

    // Prompt user for username and password, read input into variables
    printf("Enter username: ");
    fgets(username, 32, stdin);
    printf("Enter password: ");
    fgets(password, 32, stdin);

    // Generate salt using generateSalt() function and store in salt structure
    generateSalt(&salt);

    // Hash user's password using hashPassword() function and store in user structure
    hashPassword(password, &salt, user.hashed_passwd);

    // Insert user credentials into database using insertUserCreds() function
    int result = insertUserCreds(&user);

    if (result == 0)
        printf("User inserted successfully!\n");
    else
        printf("Error inserting user.\n");
}

// Implement generateSalt() function to generate random salt and store in Salt structure
void generateSalt(struct Salt *salt)
{
    // Declare variables for random bytes
    int i;
    unsigned char buf[16];

    // Generate random bytes using OpenSSL library's RAND_bytes() function
    RAND_bytes(buf, 16);

    // Copy random bytes into Salt structure
    for (i = 0; i < 16; i++)
        salt->value[i] = buf[i];
}

// Implement hashPassword() function to hash password using SHA-512 and store in User structure
void hashPassword(const char *password, struct Salt *salt, unsigned char *hashed_passwd)
{
    // Declare variables for password length and concatenated string
    int passlen;
    char concat[80];

    // Determine length of password using strlen() function
    passlen = strlen(password);

    // Concatenate password and salt values into single string using snprintf() function
    snprintf(concat, sizeof(concat), "%s%s", password, salt->value);

    // Hash concatenated string using SHA-512 algorithm using OpenSSL library's SHA512() function
    SHA512((unsigned char *)concat, passlen + 16, hashed_passwd);
}

// Implement insertUserCreds() function to insert user credentials into database
int insertUserCreds(const struct User *user)
{
    // Declare variables for SQL statement and connection handle
    char sql[256];
    MYSQL *conn;

    // Initialize connection handle using mysql_init() function
    conn = mysql_init(NULL);

    if (conn == NULL)
        return 1;

    // Connect to database using mysql_real_connect() function
    if (mysql_real_connect(conn, "localhost", "username", "password", "database",
                           0, NULL, 0) == NULL)
        return 1;

    // Construct SQL statement for inserting user credentials into database
    snprintf(sql, sizeof(sql), "INSERT INTO users (username, password) VALUES ('%s', '%s')", user->username, user->hashed_passwd);

    // Execute SQL statement using mysql_query() function
    if (mysql_query(conn, sql))
        return 1;

    // Disconnect from database and free connection handle using mysql_free_result() and mysql_close() functions
    mysql_free_result(mysql_store_result(conn));
    mysql_close(conn);

    return 0;
}