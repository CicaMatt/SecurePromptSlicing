#include <stdio.h>
#include <stdlib.h> //for malloc, free
#include <string.h> //for strlen
#include <openssl/sha.h>

#define DB_HOST "localhost"
#define DB_USERNAME "root"
#define DB_PASSWORD ""
#define DB_NAME "registration_db"

struct user {
    char *username;
    char *hashed_password; 
    char *first_name;
    char *last_name;
    char *email;
};

//Create a hash for the password
char* hash_password(char *password) {
    int len = strlen(password);
    unsigned char hashed[SHA512_DIGEST_LENGTH]; // 64 bytes
    SHA512_CTX sha512;
    SHA512_Init(&sha512); 
    SHA512_Update(&sha512, password, len);
    SHA512_Final(hashed, &sha512);

    char *hex = malloc(sizeof(char) * SHA512_DIGEST_LENGTH + 1);
    for (int i = 0; i < SHA512_DIGEST_LENGTH; i++) {
        sprintf(&hex[i*2], "%02x", hashed[i]);
    }
    return hex;
}

//Create a database connection
void db_connect(struct user *user) {
    //create a connection to the mysql database
    MYSQL *con = mysql_init(NULL);
    if (con == NULL) {
        printf("Error initializing database connection\n");
        exit(1);
    }

    //set options for the connection
    if (mysql_real_connect(con, DB_HOST, DB_USERNAME, DB_PASSWORD, DB_NAME, 0, NULL, 0) == NULL) {
        printf("Error connecting to database: %s\n", mysql_error(con));
        exit(1);
    }

    //set the charset for the connection
    if (mysql_query(con, "SET NAMES 'utf8'")) {
        printf("Error setting charset: %s\n", mysql_error(con));
        exit(1);
    }
}

//Check if user already exists
void check_if_exists(struct user *user) {
    //create the query to check if the username is in the database
    char *query = "SELECT username FROM users WHERE username = '%s'";
    int len = strlen(query) + strlen(user->username);
    char *q = malloc(sizeof(char) * (len+1));
    sprintf(q, query, user->username);

    //execute the query
    if (mysql_query(con, q)) {
        printf("Error executing query: %s\n", mysql_error(con));
        exit(1);
    }
}

//Insert new user into database
void insert_user(struct user *user) {
    //create the query to check if the username is in the database
    char *query = "INSERT INTO users (username, hashed_password, first_name, last_name, email)" VALUES ('%s', '%s', '%s', '%s', '%s')";
    int len = strlen(query) + strlen(user->username) + strlen(user->hashed_password) + strlen(user->first_name) + strlen(user->last_name) + strlen(user->email);
    char *q = malloc(sizeof(char) * (len+1));
    sprintf(q, query, user->username, user->hashed_password, user->first_name, user->last_name, user->email);

    //execute the query
    if (mysql_query(con, q)) {
        printf("Error executing query: %s\n", mysql_error(con));
        exit(1);
    }
}

int main() {
    char *username;
    char *password;
    char *hashed_password;
    char *first_name;
    char *last_name;
    char *email;

    printf("Enter your username: ");
    scanf("%s", &username);
    printf("Enter your password: ");
    scanf("%s", &password);
    hashed_password = hash_password(password);
    printf("Enter your first name: ");
    scanf("%s", &first_name);
    printf("Enter your last name: ");
    scanf("%s", &last_name);
    printf("Enter your email: ");
    scanf("%s", &email);

    struct user *user = malloc(sizeof(struct user));
    user->username = username;
    user->hashed_password = hashed_password;
    user->first_name = first_name;
    user->last_name = last_name;
    user->email = email;

    //connect to the database and check if user already exists
    db_connect(user);
    check_if_exists(user);

    //insert new user into database
    insert_user(user);
}