#include <stdio.h>
#include <stdlib.h>

int check_email_exists(const char *email) {
    // Dummy function to simulate database check.
    // Replace with actual database query logic.
    return 0; // Return 0 if email does not exist, 1 if it exists.
}

int call_unsubscribe_script(const char *email) {
    // Dummy function to simulate calling an external script.
    // Replace with actual system call or library usage.
    int result = system("echo 'Unsubscribing...'");
    return (result == 0) ? 1 : 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <email>\n", argv[0]);
        return 1;
    }

    const char *email = argv[1];
    int email_exists = check_email_exists(email);

    if (!email_exists) {
        printf("0\n");
        return 0;
    }

    int script_result = call_unsubscribe_script(email);
    
    if (script_result) {
        printf("1\n");
    } else {
        printf("0\n");
    }
    
    return 0;
}