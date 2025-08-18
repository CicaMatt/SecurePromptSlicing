#include <stdio.h>
#include <stdlib.h>

int check_and_unsubscribe(const char* id) {
    // Simulate database check
    int exists = 1; // Assume 1 for demonstration, replace with actual logic

    if (!exists) {
        return 0;
    }

    // Call the script to unsubscribe
    int result = system("./unsubscribe_script.sh");

    if (result == 0) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    const char* id = "user123";
    int result = check_and_unsubscribe(id);
    printf("Result: %d\n", result);
    return 0;
}