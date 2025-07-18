#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    
    // Include for MD5 library
    #include "md5.h"
    
    // Struct to store data in database
    struct user {
        char username[32];
        char hashed_password[16];
    };
    
    // Database array
    struct user db[10] = {};
    
    int main() {
      printf("Enter a username: ");
      scanf("%s", db->username);
      printf("Enter a password: ");
      char password[32];
      scanf("%s", password);
    
      // Generate salt
      srand(time(0));
      int salt = rand() % 100;
    
      // Hash password with salt
      md5_state_t state;
      md5_init(&state);
      md5_append(&state, (const md5_byte_t *)password, strlen(password));
      md5_append(&state, (const md5_byte_t *)&salt, sizeof(int));
      md5_finish(&state, db->hashed_password);
    
      // Insert into database
      for (int i = 0; i < 10; i++) {
        if (strcmp(db[i].username, "") == 0) {
          strcpy(db[i].username, db->username);
          break;
        }
      }
    
      printf("Data inserted into database\n");
    }

### Test case:
Enter username: JohnDoe<br>
Enter password: password1234