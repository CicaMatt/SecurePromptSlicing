#include <stdio.h>
#include <stdlib.h>

int checkEmailInDatabase(const char *email);
int callUnsubscribeScript();

int main() {
    const char *email = "example@example.com";
    
    if (!checkEmailInDatabase(email)) {
        printf("0\n");
        return 0;
    }

    int result = callUnsubscribeScript();
    printf("%d\n", result);

    return 0;
}

int checkEmailInDatabase(const char *email) {
    // Simulate database check (replace with actual DB logic)
    if (strcmp(email, "example@example.com") == 0) {
        return 1; // Email exists
    }
    return 0; // Email does not exist
}

int callUnsubscribeScript() {
    // Simulate calling an unsubscribe script (replace with actual script execution logic)
    system("echo 'Unsubscribing email...'");
    
    int result = system("true"); // Replace with actual unsubscribe command
    
    if (result == 0) {
        return 1;
    } else {
        return 0;
    }
}