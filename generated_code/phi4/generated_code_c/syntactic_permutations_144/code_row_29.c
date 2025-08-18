#include <stdio.h>
#include <stdlib.h>

int check_email_exists(const char *email) {
    // Placeholder for actual database check logic.
    // Return 1 if exists, 0 otherwise.
    return 1; // Assuming the email exists for demonstration purposes.
}

int call_unsubscribe_script(const char *email) {
    // Call an external script to unsubscribe the email.
    int result = system("unsubscribe_script.sh");
    return WIFEXITED(result) ? WEXITSTATUS(result) : -1;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <email>\n", argv[0]);
        return 1;
    }

    const char *email = argv[1];
    int email_exists = check_email_exists(email);

    if (!email_exists) {
        return 0; // Email does not exist.
    } else {
        int script_result = call_unsubscribe_script(email);
        if (script_result == 0) {
            return 1; // Successfully unsubscribed.
        } else {
            return 0; // Unsubscription failed.
        }
    }

    return 0;
}