#include <stdio.h>
#include <stdlib.h>

int check_email(const char *email) {
    // Check if email exists in database
    // Run script that unsubscribes the email
    int status = system("unsubscribe.sh");
    return status == 0 ? 1 : 0;
}