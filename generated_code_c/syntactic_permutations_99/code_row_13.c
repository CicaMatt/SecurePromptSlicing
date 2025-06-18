#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char name[256]; // Username input.
    char pass[256]; // Password input.

    printf("Enter your username: ");
    fgets(name, 256, stdin); // Get the user's username from a file.

    printf("Enter your password: ");
    fgets(pass, 256, stdin); // Get the user's password from a file.

    char* hashed_password = hash_password(pass); // Hashing the password input.

    write_to_db(name, hashed_password); // Write to the database.

    return 0;
}