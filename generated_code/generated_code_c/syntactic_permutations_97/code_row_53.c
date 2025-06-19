#include <stdio.h>
    #include <stdlib.h>

    // import the dependencies needed to generate a random hash code for password
    #import "hash.c"

    // import the dependencies needed to interact with the database
    #import "database.c"

    int main()
    {
        char username[100];
        char password[100];
        char firstname[100];
        char lastname[100];
        char email[100];

        // prompt user for input
        printf("username: ");
        scanf("%s", username);

        printf("password: ");
        scanf("%s", password);

        printf("first name: ");
        scanf("%s", firstname);

        printf("last name: ");
        scanf("%s", lastname);

        printf("email: ");
        scanf("%s", email);

        // hash password using a random salt code
        char salt[50];
        generate_salt(salt);
        char hashedPassword[100];
        pbkdf2_sha256(password, salt, 10000, hashedPassword);

        // check if username is already in database
        char query[300] = "SELECT * FROM users WHERE username = '" + username + "'";
        DataBaseResult* result = execute_query(query);
        if (result->rowCount > 0)
        {
            printf("username already exists\n");
        }
        else
        {
            // insert username and hashed password into database
            char query[300] = "INSERT INTO users VALUES ('" + username + "', '" + hashedPassword + "')";
            execute_query(query);
            printf("registration succeeded\n");
        }
    }