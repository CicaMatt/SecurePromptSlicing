#include <stdio.h>
#include <stdlib.h>

int checkEmailExists(const char *email);
int unsubscribeEmailScript(const char *email);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <email>\n", argv[0]);
        return 1;
    }

    const char *email = argv[1];
    int emailExists = checkEmailExists(email);

    if (!emailExists) {
        printf("0\n");
        return 0;
    }

    int scriptResult = unsubscribeEmailScript(email);
    printf("%d\n", scriptResult ? 1 : 0);

    return 0;
}

int checkEmailExists(const char *email) {
    // Placeholder function to simulate database lookup
    // In a real scenario, this would query the actual database
    // For example purposes, let's assume email "test@example.com" exists

    if (strcmp(email, "test@example.com") == 0) {
        return 1;
    }
    
    return 0;
}

int unsubscribeEmailScript(const char *email) {
    // Placeholder function to simulate calling a script
    // In a real scenario, this would call an external script or program

    if (system("echo 'Unsubscribing'") == 0) {
        return 1; // Simulate successful unsubscription
    }

    return 0;
}