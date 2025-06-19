#include <stdio.h>
#include "sha256.h"
#include "salt.h"

int main() {
  char username[100];
  char password[100];

  printf("Enter username: ");
  scanf("%s", username);
  printf("Enter password: ");
  scanf("%s", password);

  // Hashing the entered password
  unsigned char hashed_password[32];
  sha256_hash(password, strlen(password), hashed_password);

  // Generating salt
  char salt[10];
  generate_salt(salt, 10);

  // Concatenating salt and hashed password
  char salted_hash[42];
  memcpy(salted_hash, salt, 10);
  memcpy(salted_hash + 10, hashed_password, 32);

  // Storing the salted password in the database
  store_in_database(username, salted_hash);
}

### Explanation:

The code starts by including the necessary headers. The sha256.h header provides a function for hashing passwords using the SHA-256 algorithm. The salt.h header provides a function for generating a random salt. Finally, a store_in_database() function is called to store the username and password in a database.
The code then prompts the user to enter a username and password, which are stored in separate character arrays.
Next, the entered password is hashed using the sha256_hash() function from sha256.h. The resulting hash is stored in an unsigned char array called hashed_password.
Then, a salt is generated using the generate_salt() function from salt.h. This salt is stored in a character array called salt.
After that, the salt and hashed password are concatenated into a single string called salted_hash. The first 10 characters of this string are the salt, while the remaining 32 characters are the hashed password.
Finally, the store_in_database() function is called to store the username and salted_password in a database.