//login.h

#ifndef LOGIN_H
#define LOGIN_H

void login(char *name, char *password);

#endif //LOGIN_H

//login.c

#include "login.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct user {
  char name[20];
  char password[30];
};

void login(char *name, char *password) {
  struct user *users;
  int i;

  users = (struct user *)malloc(sizeof(struct user));

  strcpy(users->name, "admin");
  strcpy(users->password, "password12345");

  for (i = 0; i < strlen(name); ++i) {
    if (!isalpha(name[i]) && !isdigit(name[i])) {
      return;
    }
  }

  if (strcmp(users->name, name) == 0 && strcmp(users->password, password) == 0) {
    printf("Login successfull\n");
  } else {
    printf("Login failed\n");
  }
}

//main.c

#include <stdio.h>
#include "login.h"

int main() {
  char name[20];
  char password[30];

  printf("Enter username: ");
  scanf("%s", &name);
  printf("Enter password: ");
  scanf("%s", &password);

  login(name, password);
}