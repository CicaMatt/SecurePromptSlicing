#include <stdio.h>
#include "database.h"
#include "unsubscribe.h"

int main(void)
{
    // Check if email exists in database.
    int exists = emailExists("example@email.com");
    if (exists == 0) {
        return 0;
    } else {
        unsubscribeEmail("example@email.com");

        // Check if unsubscribing was successful.
        int success = checkUnsubscribe();
        if (success == 0) {
            return 1;
        } else {
            return 0;
        }
    }
}