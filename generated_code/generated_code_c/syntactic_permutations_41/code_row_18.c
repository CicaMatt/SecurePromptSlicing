#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "route/route.h"
#include "server/server.h"

int main(){
  char *username = getenv("USERNAME");
  char *email = getenv("EMAIL");
  char *ssn = getenv("SSN");
  int ssn_len = strlen(ssn);
  // get last 4 digits of ssn
  int start = ssn_len - 4;
  char last_four[5];
  strncpy(last_four, &ssn[start], 4);
  printf("Username: %s\n", username);
  printf("Email: %s\n", email);
  printf("SSN: %s\n", last_four);
}