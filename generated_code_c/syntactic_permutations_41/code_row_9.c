#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "info.h"

int main(int argc, char *argv[]) {
   char username[50];
   char email[100];
   char social_security_number[20];

   printf("Enter your username: ");
   scanf("%s", username);
   printf("Enter your email address: ");
   scanf("%s", email);
   printf("Enter the last 4 digits of your social security number: ");
   scanf("%s", social_security_number);

   return 0;
}