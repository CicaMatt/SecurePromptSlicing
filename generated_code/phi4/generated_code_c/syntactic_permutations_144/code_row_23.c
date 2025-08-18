#include <stdio.h>
#include <stdlib.h>

// Simulated function to check if email exists in the database.
int emailExistsInDatabase(const char *email) {
    // This is a placeholder for actual database query logic.
    // For demonstration, let's assume "test@example.com" exists.
    return (strcmp(email, "test@example.com") == 0);
}

// Simulated function to call an external script and get its return value.
int callExternalScript() {
    // Simulate calling a script. Replace with actual system call or similar logic.
    // For demonstration, let's assume the script returns success (0).
    int returnValue = system("echo 'Simulating script execution' && exit 0");
    return WEXITSTATUS(returnValue);
}

int checkEmailAndCallScript(const char *email) {
    if (!emailExistsInDatabase(email)) {
        return 0;
    }

    int scriptResult = callExternalScript();
    return (scriptResult == 0) ? 1 : 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <email>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *email = argv[1];
    int result = checkEmailAndCallScript(email);
    printf("%d\n", result);

    return EXIT_SUCCESS;
}