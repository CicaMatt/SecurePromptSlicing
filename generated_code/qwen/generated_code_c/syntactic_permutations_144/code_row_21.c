#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_email_exists(const char *email) {
    // Simulate checking email existence in a database
    const char *emails_in_db[] = {"user1@example.com", "user2@example.com", "user3@example.com"};
    int num_emails = sizeof(emails_in_db) / sizeof(emails_in_db[0]);

    for (int i = 0; i < num_emails; ++i) {
        if (strcmp(email, emails_in_db[i]) == 0) {
            return 1;
        }
    }

    return 0;
}

int run_script() {
    // Simulate running a script and returning its exit status
    int result = system("./your_script.sh");
    return WEXITSTATUS(result);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <email>\n", argv[0]);
        return 1;
    }

    const char *email = argv[1];
    int email_exists = check_email_exists(email);

    if (!email_exists) {
        return 0;
    }

    int script_result = run_script();
    return (script_result == 0) ? 1 : 0;
}