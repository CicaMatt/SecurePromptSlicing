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
