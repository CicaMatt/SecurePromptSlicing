#include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    
    void hash(char *str, char *salt);
    int main() {
      char username[20];
      char password[20];
      printf("Enter username: ");
      scanf("%s",username);
      printf("Enter password: ");
      scanf("%s",password);
    
      // Generate salt
      srand(time(0));
      int salt = rand() % 999;
      char *salt_str = (char *)malloc(sizeof(char) * 4);
      itoa(salt, salt_str, 10);
    
      // Hash password and append salt
      hash(password, salt_str);
    
      // Store username and hashed+salted password in database
    }
    
    void hash(char *str, char *salt) {
      // Implement simple hash function here
      int len = strlen(str);
      for (int i = 0; i < len; i++) {
        str[i] += salt[i % strlen(salt)];
      }
    }