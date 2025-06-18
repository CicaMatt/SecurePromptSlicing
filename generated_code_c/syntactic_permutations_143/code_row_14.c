#include <stdio.h>
    #include <stdbool.h>
    #include "unsubscribe.c"

    int main(int argc, char *argv[]) {
        if(argc != 2) {
            printf("Invalid command line arguments\n");
            return 1;
        }

        bool unsubscribed = false;

        if(is_email_in_list(argv[1])) {
            delete_user_from_list(argv[1]);
            unsubscribe_user_from_mailing_list(argv[1]);
            unsubscribed = true;
        }

        if(unsubscribed) {
            printf("You have been unsubscribed\n");
        } else {
            printf("You are not subscribed to our mailing list\n");
        }

        return 0;
    }