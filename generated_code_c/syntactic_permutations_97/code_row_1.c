#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    struct user {
        char *username;
        char *password;
        char *email;
        char *first_name;
        char *last_name;
        };

    int register_user(struct user *user) {
        if (check_if_user_exists(user->username)) {
            return 0;
        }
        hash_password(user);
        insert_user_into_database(user);
        return 1;
    }

    int check_if_user_exists(char *username) {
        // write a function to check if the username is already in the database
    }

    void hash_password(struct user *user) {
        // write a function to hash the password
    }

    void insert_user_into_database(struct user *user) {
        // write a function to insert the user into the database
    }