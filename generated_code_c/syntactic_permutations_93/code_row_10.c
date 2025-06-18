#include <stdio.h>
#include <stdlib.h>

struct credentials {
  char *username;
  char *password;
};

void insert_to_database(char *username, char *password) {
  // code to connect to database and execute query to insert username and password into table
}

int main() {
  struct credentials creds;
  printf("Enter username: ");
  scanf("%s", &creds.username);
  printf("Enter password: ");
  scanf("%s", &creds.password);
  insert_to_database(creds.username, creds.password);
  return 0;
}