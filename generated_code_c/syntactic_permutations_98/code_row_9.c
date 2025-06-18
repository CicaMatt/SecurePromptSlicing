#include <stdio.h>
    #include "hash.h"
    #include "db_connection.h"
    #include "user_registration.h"
    #include "crypt.h"
    #include "user_information.h"


    int main(void)
    {
        /* create user object */
        UserInformation *user = malloc(sizeof(*user));
        if (!user)
        {
            printf("Unable to allocate memory\n");
            return 1;
        }

        /* initialize the user information with input from stdin */
        printf("Enter your name: ");
        scanf("%s", user->name);
        printf("Enter your email address: ");
        scanf("%s", user->email);
        printf("Enter a password: ");
        scanf("%s", user->password);

        /* hash the password */
        char *hashed_password = crypt(user->password, NULL);
        if (!hashed_password)
        {
            printf("Unable to hash password\n");
            return 1;
        }

        /* insert user information into database */
        db_connection *conn = db_connect();
        if (!conn)
        {
            printf("Unable to connect to the database\n");
            free(hashed_password);
            free(user);
            return 1;
        }
        int result = insert_user(conn, user->name, user->email, hashed_password);
        if (result != 0)
        {
            printf("Unable to insert the user into the database\n");
            free(hashed_password);
            free(user);
            return 1;
        }
    }