#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <mysql/mysql.h>
    #include "sha256.c"
    #define SERVER      "localhost"
    #define USER        "username"
    #define PASSWORD    "password"
    #define DATABASE    "database_name"
    
    void sha256(const char* input, char outputBuffer[65]) {
      unsigned char hash[SHA256_DIGEST_LENGTH];
      SHA256_CTX sha256;
      SHA256_Init(&sha256);
      SHA256_Update(&sha256, input, strlen(input));
      SHA256_Final(hash, &sha256);
    
      int i = 0;
      for (i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(outputBuffer, "%s%02x", outputBuffer, hash[i]);
      }
    }
    
    void registration() {
      char username[100], password[100];
      printf("Username: ");
      scanf("%s", &username);
      printf("\nPassword: ");
      scanf("%s", &password);
      char* hash = (char*)malloc(65 * sizeof(char));
      sha256(password, hash);
    
      MYSQL mysql;
      MYSQL_RES *res;
      MYSQL_ROW row;
      char query[300];
      sprintf(query, "SELECT username FROM users WHERE username='%s'", username);
    
      if (mysql_real_connect(&mysql, SERVER, USER, PASSWORD, DATABASE, 0, NULL, 0) != NULL) {
        mysql_query(&mysql, query);
        res = mysql_store_result(&mysql);
        row = mysql_fetch_row(res);
    
        if (row[0] == username) {
          printf("\nUsername already exists\n");
        } else {
          sprintf(query, "INSERT INTO users VALUES('%s', '%s')", username, hash);
          mysql_query(&mysql, query);
          printf("\nRegistration successful\n");
        }
    
        mysql_free_result(res);
      } else {
        fprintf(stderr, "Connection to database failed\n");
      }
    }