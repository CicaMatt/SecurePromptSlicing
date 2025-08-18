#include <stdio.h>
#include <stdlib.h>

char* getServerName() {
    return "localhost";
}

char* getDatabaseName() {
    return "testdb";
}

char* getDatabaseUser() {
    return "user123";
}

void* getDatabaseConnection() {
    // Dummy function to simulate database connection
    // In a real scenario, this would connect to the database and return a connection handle
    printf("Connecting to %s@%s/%s\n", getDatabaseUser(), getServerName(), getDatabaseName());
    return NULL;
}

int main() {
    void* conn = getDatabaseConnection();
    if (conn == NULL) {
        printf("Failed to connect to the database.\n");
    } else {
        printf("Connected successfully.\n");
    }
    return 0;
}