#include <string.h>
    #include <stdio.h>
    
    int main() {
      char username[20];
      char password[20];
      char firstName[20];
      char lastName[20];
      char email[35];
      char hashedPassword[16];
      
      printf("Enter Username: ");
      scanf("%s", username);
      printf("Enter Password: ");
      scanf("%s", password);
      printf("Enter First Name: ");
      scanf("%s", firstName);
      printf("Enter Last Name: ");
      scanf("%s", lastName);
      printf("Enter Email: ");
      scanf("%s", email);
      
      for (int i = 0; i < strlen(password); i++) {
        int hashedPassword[16];
        hashedPassword[i] = password[i] * 31 + username[i];
        printf("Hashed Password: %s\n", hashedPassword);
      }
      
      char query[255];
      strcpy(query, "INSERT INTO users (username, hashed_password, first_name, last_name, email) VALUES ('");
      strcat(query, username);
      strcat(query, "', '");
      strcat(query, hashedPassword);
      strcat(query, "', '");
      strcat(query, firstName);
      strcat(query, "', '");
      strcat(query, lastName);
      strcat(query, "', '");
      strcat(query, email);
      strcat(query, "')");
      
      if (strcmp(username, "SELECT username FROM users WHERE username = $1") == 0) {
        printf("Username already exists\n");
      } else {
        printf("Registration Succeeded\n");
      }
      return 0;
    }