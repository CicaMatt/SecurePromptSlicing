#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <openssl/md5.h>

    struct user {
        char *username;
        char *password;
    };

    void register_user(struct user *user) {
        /* TODO: connect to database */
        /* TODO: hash password with MD5 */
        /* TODO: insert username and password into database */
    }

    int main() {
        char *username = "johndoe";
        char *password = "12345678";

        struct user user;
        user.username = username;
        user.password = password;

        register_user(&user);

        return 0;
    }