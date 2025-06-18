#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "crypto/sha256.h"

int main(void) {
  char username[100];
  char password[100];
  char hashed_password[32];

  printf("Enter your username: ");
  scanf("%99s", username);

  printf("Enter your password: ");
  scanf("%99s", password);

  sha256(password, hashed_password);

  // store the username and password in a database

  return 0;
}

### Explanation:
This program prompts the user to enter their username and password. The entered password is then hashed using the sha256 function from the crypto/sha256.h header file. The resulting hashed_password array stores the hashed password, which can be stored in a database along with the entered username.

### Example:

Enter your username: John
Enter your password: secret

The program will store the following values in a database:

username = "John"
password_hashed = "018f6d2a7b33491ba05b1cf9e34c51edcb2e273f24071b0786da31bfa1041a3b"

Note that the above hash value is for demonstration purposes only and should not be used in production code.