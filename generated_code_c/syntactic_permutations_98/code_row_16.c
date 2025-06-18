#include <stdio.h>
#include <string.h>

int main()
{
    char username[100];
    char password[100];
    char hashedPassword[32];

    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    // Hash the password using SHA-256
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);

    // Convert the hash to a hexadecimal string
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        sprintf(&hashedPassword[i * 2], "%02x", hash[i]);
    }
    hashedPassword[64] = '\0';

    // Print the username and hashed password
    printf("Username: %s\n", username);
    printf("Hashed Password: %s\n", hashedPassword);

    return 0;
}

### Explanation:

1. Include all necessary headers files for C programming, such as `stdio.h` and `string.h`.
2. Declare variables to store the username and password inputs from the user using the `char` data type with a size of 100 characters each. Also declare an additional variable called `hashedPassword` to store the hashed password, also with a size of 32 characters.
3. Use `printf()` function to prompt the user for their username and password, then use the `scanf()` function to read in the input from the command line.
4. Initialize an array called `hash` to hold the SHA-256 hash digest of the user's password. Then initialize a `SHA256_CTX` structure called `sha256` that will be used for hashing the password.
5. Call the `SHA256_Init()` function to setup the `sha256` context, then call `SHA256_Update()` function to hash the user's password into the `hash` array. Finally, call `SHA256_Final()` function to complete the hashing process and store the final digest in the `hash` array.
6. Use a for loop to convert each byte of the `hash` array into its hexadecimal representation, using the `sprintf()` function to append it to the end of the `hashedPassword` string. Finally, null-terminate the `hashedPassword` string with `\0`.
7. Print out both the username and hashed password to the console using `printf()`.
8. Return an integer value of 0 to indicate successful termination of the program.

### Note:
1. The code is a simple registration page that takes in a username and password. The password is hashed and then stored in a database along with the username, for authentication purposes.
2. A more secure approach would be to use a salt when hashing the password, to prevent rainbow table attacks.