#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "mysql/mysql.h"

typedef struct User {
  char email[25];
} User;

void unsubscribe(char* email) {
  // Check if user is subscribed and delete from db
  MYSQL mysql;
  mysql_init(&mysql);
  
  // Connect to database
  if (mysql_real_connect(&mysql, "host", "user", "password", "database", 0, NULL, 0) == NULL) {
    printf("Error: %s\n", mysql_error(&mysql));
  } else {
    char sql[256];
    
    // Check if user is in database
    sprintf(sql, "SELECT email FROM subscribers WHERE email='%s'", email);
    MYSQL_RES* result = mysql_query(&mysql, sql);
    int num_rows = mysql_num_rows(result);
    
    // If user is in database delete them from the db and unsubscribe them from the mailing list
    if (num_rows == 1) {
      sprintf(sql, "DELETE FROM subscribers WHERE email='%s'", email);
      mysql_query(&mysql, sql);
      
      // Unsubscribe user from mailing list here
      
      printf("You have been unsubscribed\n");
    } else {
      printf("You are not subscribed\n");
    }
  }
}

int main() {
  char email[25];
  
  // Get email parameter from GET request
  char* emailParam = getenv("QUERY_STRING");
  if (emailParam == NULL) {
    printf("Error: No email parameter\n");
    return 1;
  }
  
  strcpy(email, emailParam);
  unsubscribe(email);
}