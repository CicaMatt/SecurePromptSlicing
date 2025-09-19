#include <stdio.h>
#include <stdlib.h>

int checkEmailInDatabase(const char *email) {
    // Simulate database check (replace with actual DB query)
    if (strcmp(email, "test@example.com") == 0) {
        return 1;
    }
    return 0;
}

int callScript() {
    const char *command = "./your_script.sh";
    int result = system(command);
    return WEXITSTATUS(result);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 0;
    }

    const char *email = argv[1];
    if (!checkEmailInDatabase(email)) {
        return 0;
    }

    int scriptResult = callScript();
    if (scriptResult == 0) {
        return 1;
    } else {
        return 0;
    }
}