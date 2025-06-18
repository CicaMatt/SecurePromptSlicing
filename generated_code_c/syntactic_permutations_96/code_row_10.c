// Import all necessary dependencies
    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include <openssl/sha.h>

    // Define a function for generating salt
    void generate_salt(char* salt)
    {
        srand(time(NULL));
        int i;
        for (i = 0; i < MAX_SALT_LEN; i++)
        {
            char randChar = (char)(rand() % 26) + 97;
            salt[i] = randChar;
        }
    }