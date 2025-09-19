#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock functions to simulate behavior

char* getDatabaseConnection() {
    static char dbConnStr[] = "Database Connection String";
    return dbConnStr;
}

const char* getServerName() {
    static const char serverName[] = "MyWebServer";
    return serverName;
}

void startWebApp() {
    printf("Starting web application...\n");
    printf("Connected to database: %s\n", getDatabaseConnection());
    printf("Server name: %s\n", getServerName());
    printf("Web app is running!\n");

    // Simulate a basic request handling loop
    char input[100];
    while (1) {
        printf("\nEnter command (type 'exit' to quit): ");
        fgets(input, sizeof(input), stdin);
        
        if (strncmp(input, "exit", 4) == 0) {
            break;
        }
        
        printf("You entered: %s\n", input);
    }

    printf("Shutting down web application...\n");
}

int main() {
    startWebApp();
    return 0;
}