#include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    
    #define MAX_EMAIL_LENGTH 50
    #define MAX_NAME_LENGTH 20
    
    struct emailList {
      char firstName[MAX_NAME_LENGTH];
      char lastName[MAX_NAME_LENGTH];
      char emailAddress[MAX_EMAIL_LENGTH];
    };
    
    int main() {
      
      printf("Enter your email address to unsubscribe: ");
      scanf("%s", email);
      
      // Check if email is in the database
      if (isEmailInDatabase(email)) {
        removeFromDatabase(email);
        printf("You have been removed from our mailing list.");
      } else {
        printf("You are not in our mailing list.");
      }
    }
    
    // Connects to the database and checks if the email address is in the database
    int isEmailInDatabase(char *email) {
      
      struct emailList record;
      
      // Open the file containing the email addresses
      FILE *file = fopen("emailAddresses.txt", "r");
      
      while (fscanf(file, "%s %s %s", &record.firstName, &record.lastName, &record.emailAddress) != EOF) {
        if (strcmp(email, record.emailAddress) == 0) {
          fclose(file);
          return 1; // Email is in the database
        }
      }
      
      fclose(file);
      return 0; // Email is not in the database
    }
    
    // Removes an email address from the database
    void removeFromDatabase(char *email) {
      struct emailList record;
      FILE *file = fopen("emailAddresses.txt", "r+");
      
      while (fscanf(file, "%s %s %s", &record.firstName, &record.lastName, &record.emailAddress) != EOF) {
        if (strcmp(email, record.emailAddress) == 0) {
          break; // Found the email address to remove
        }
      }
      
      // Rewrite the file without the email address being removed
      rewind(file);
      while (fscanf(file, "%s %s %s", &record.firstName, &record.lastName, &record.emailAddress) != EOF) {
        if (strcmp(email, record.emailAddress) == 0) {
          continue; // Skip the email address being removed
        }
        
        fprintf(file, "%s %s %s\n", &record.firstName, &record.lastName, &record.emailAddress);
      }
      
      fclose(file);
    }