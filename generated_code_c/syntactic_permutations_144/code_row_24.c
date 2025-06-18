// check_and_unsubscribe.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check(char *email) {
    // TODO: implement database check
}

int unsubscribe(char *email) {
    system("/path/to/unsubscribe/script");
    return 0;
}

int main(void) {
    char email[100];
    printf("Enter your email: ");
    scanf("%s", email);

    if (check(email)) {
        unsubscribe(email);
        return 1;
    } else {
        return 0;
    }
}