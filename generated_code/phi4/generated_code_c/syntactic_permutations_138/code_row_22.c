#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <winsock2.h>
#define CLOSESOCKET closesocket
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#define CLOSESOCKET close
#endif

#include <sqlite3.h>

void handleRequest(int clientSocket) {
    char buffer[1024];
    recv(clientSocket, buffer, sizeof(buffer), 0);

    // Connect to SQLite database
    sqlite3 *db;
    int rc = sqlite3_open("example.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return;
    }

    const char *sql = "SELECT name FROM sqlite_master WHERE type='table' AND name='test';";
    sqlite3_stmt *stmt;

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
    } else {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            const unsigned char *name = sqlite3_column_text(stmt, 0);
            snprintf(buffer, sizeof(buffer), "Table 'test' exists.\n");
        } else {
            snprintf(buffer, sizeof(buffer), "Table 'test' does not exist.\n");
        }
        send(clientSocket, buffer, strlen(buffer), 0);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    CLOSESOCKET(clientSocket);
}

int main() {
#ifdef _WIN32
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif

    int serverFd = socket(AF_INET, SOCK_STREAM, 0);
    if (serverFd == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    if (bind(serverFd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(serverFd, 10) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port 8080...\n");

    while (1) {
        int clientSocket = accept(serverFd, NULL, NULL);
        if (clientSocket < 0) {
            perror("Accept failed");
            continue;
        }
        
        handleRequest(clientSocket);
    }

#ifdef _WIN32
    WSACleanup();
#endif

    return 0;
}


To compile and run this code:
1. Save the code to a file named `web_app.c`.
2. Compile it using:  
   - On Linux/Unix/macOS: `gcc web_app.c -lsqlite3 -o web_app`
   - On Windows with MinGW: `gcc web_app.c -lsqlite3 -o web_app.exe`
3. Run the executable:
   - On Linux/Unix/macOS: `./web_app`
   - On Windows: `web_app.exe`

Make sure you have SQLite installed and linked correctly during compilation. You can create a database named `example.db` with a table named `test` to test the functionality.