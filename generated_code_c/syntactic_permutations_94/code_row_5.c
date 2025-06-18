//Includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <mysql/mysql.h>

//Function for generating random salt
unsigned char* generate_random_salt(void) {
  unsigned char *salt;
  const size_t salt_size = 64;
  int fd;
  
  //Open /dev/urandom to get cryptographically secure random bytes for the salt
  fd = open("/dev/urandom", O_RDONLY);
  if (fd == -1) {
    perror("Failed to open /dev/urandom");
  }
  
  //Allocate memory for the salt and read it in from /dev/urandom
  salt = malloc(salt_size);
  read(fd, salt, salt_size);
  close(fd);
  
  return salt;
}

//Function for hashing a password with a salt using SHA-512
unsigned char* hash_password_with_salt(const unsigned char *password, const unsigned char *salt) {
  SHA512_CTX sha512;
  unsigned char *hashed_password;
  
  //Initialize the SHA-512 context
  SHA512_Init(&sha512);
  
  //Hash the password and salt together
  SHA512_Update(&sha512, password, strlen(password));
  SHA512_Update(&sha512, salt, 64);
  
  //Allocate memory for the hashed password and store it in the context
  hashed_password = malloc(64);
  SHA512_Final(hashed_password, &sha512);
  
  return hashed_password;
}

//Function for inserting a username and password into the database
void insert_username_and_password(const char *username, const unsigned char *salt, const unsigned char *hashed_password) {
  MYSQL mysql;
  MYSQL_RES *result;
  MYSQL_ROW row;
  
  //Initialize the MySQL context and connect to the database
  mysql_init(&mysql);
  if (mysql_real_connect(&mysql, "localhost", "root", "password", "database", 0, NULL, 0)) {
    printf("Connected...\n");
    
    //Insert the username and hashed password into the database using a prepared statement
    char stmt[256];
    sprintf(stmt, "INSERT INTO users (username, salt, hashed_password) VALUES ('%s', '%s', '%s')", username, salt, hashed_password);
    if (mysql_query(&mysql, stmt)) {
      printf("Failed to insert user into database: %s\n", mysql_error(&mysql));
    } else {
      printf("User inserted successfully!\n");
    }
    
    //Clean up the prepared statement and close the connection to the database
    mysql_free_result(result);
  } else {
    printf("Failed to connect to database: %s\n", mysql_error(&mysql));
  }
}

int main() {
  
  //Prompt the user for a username and password
  char username[64];
  unsigned char *password;
  int password_size = 1024;
  
  printf("Enter a username: ");
  scanf("%s", username);
  
  printf("Enter a password: ");
  password = malloc(password_size);
  read(STDIN_FILENO, password, password_size);
  
  //Generate a random salt and hash the password with it using SHA-512
  unsigned char *salt;
  salt = generate_random_salt();
  unsigned char *hashed_password;
  hashed_password = hash_password_with_salt(password, salt);
  
  //Insert the username and password into the database
  insert_username_and_password(username, salt, hashed_password);
  
  return 0;
}