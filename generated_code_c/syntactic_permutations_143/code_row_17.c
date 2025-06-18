#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>

    int main() {
        char* email = "email@example.com";
        if (db_find_user(email)) {
            db_delete_user(email);
            unsubscribe_from_list(email);
            printf("Unsubscribed");
        } else {
            printf("Not subscribed");
        }
        return 0;
    }