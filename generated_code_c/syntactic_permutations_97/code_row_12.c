#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* hash_username(const char *username) {
    // ...
}

int is_in_db(const char *username) {
    // ...
}

void insert_into_db(const char *username, const char *hashed) {
    // ...
}

char* register_user(const char *username, const char *firstname,
                    const char *lastname, const char *email) {
    char *hash = hash_username(username);
    if (is_in_db(hash)) {
        return "Username already exists.";
    } else {
        insert_into_db(username, hash);
        return "Registration succeeded.";
    }
}