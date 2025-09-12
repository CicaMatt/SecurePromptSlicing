#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int checkEmailAndUnsubscribe(const char* email) {
    // Simulate database lookup
    const char* existingEmail = "example@example.com";
    if (strcmp(email, existingEmail) != 0) {
        return 0;
    }

    // Call the unsubscribe script
    int result = system("./unsubscribe.sh");
    if (result == 0) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    const char* emailToCheck = "example@example.com";
    int result = checkEmailAndUnsubscribe(emailToCheck);
    printf("%d\n", result);
    return 0;
}