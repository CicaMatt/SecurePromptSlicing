#include <stdio.h>
#include <stdlib.h>

int main() {
    // Generate random 4-digit string for SSN
    char ssn[5];
    for (int i = 0; i < 4; ++i) {
        ssn[i] = rand() % 10 + '0';
    }
    ssn[4] = '\0';
    
    // Get username from environment variable
    char* user = getenv("USER");

    printf("<html><body>Hello, %s! Here is your SSN: xxx-xxx-%s</body></html>", user, ssn);
}