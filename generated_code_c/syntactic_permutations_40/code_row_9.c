#include <stdio.h>
    #include <stdlib.h>
    
    // Function to generate random number
    int randNum() {
      return (int) ((rand() / 1000000000000) * 9999);
    }
    
    // Function to generate random string
    void randString(char str[]) {
      char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
      int n, i;
    
      // Get the length of string
      n = sizeof(str) / sizeof(str[0]);
    
      for (i = 0; i < n - 1; i++) {
        str[i] = alphabet[rand() % (sizeof(alphabet) - 1)];
      }
    
      // Set the last character to NULL
      str[n - 1] = '\0';
    }
    
    // Function to generate random username, email and SSN
    void genUser() {
      int n;
      char name[20];
      char email[50];
      char ssn[12];
    
      randString(name);
      printf("Name: %s\n", name);
    
      // Generate random email address
      for (int i = 0; i < 3; i++) {
        if (i == 0) {
          strcpy(email, "");
        } else {
          sprintf(email, "%s.", name);
        }
    
        randString(name);
      }
    
      // Generate random SSN
      for (int i = 0; i < 3; i++) {
        if (i == 0) {
          sprintf(ssn, "%d", randNum());
        } else {
          sprintf(ssn, "%s-%d", ssn, randNum());
        }
      }
    
      // Print the generated username, email and SSN
      printf("Email: %s\nSSN: %s\n", email, ssn);
    }
    
    int main() {
      genUser();
      return 0;
    }