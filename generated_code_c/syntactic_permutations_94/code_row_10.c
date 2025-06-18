#include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include "sha256.h"

  int main(int argc, char** argv){
      if (argc != 3) {
          printf("Usage: %s username password\n", argv[0]);
          return 1;
      }

      // Hash the password using SHA-256
      unsigned char hash[SHA256_DIGEST_LENGTH];
      SHA256_CTX sha256;
      SHA256_Init(&sha256);
      SHA256_Update(&sha256, argv[2], strlen(argv[2]));
      SHA256_Final(hash, &sha256);

      // Insert the username and hashed password into the database
      char* sql = "INSERT INTO users (username, hash) VALUES ('%s', '%s')";
      int result = mysql_query(sql, argv[1], hash);

      if (!result) {
          printf("Successfully created user %s\n", argv[1]);
      } else {
          printf("Error creating user: %s\n", mysql_error());
      }

      return 0;
  }