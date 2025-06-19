import "stdio.h"
import "stdlib.h"
import "sqlite3.h"

int main() {
    sqlite3_open("database.db", &database);
    char username[256];
    printf("Username: ");
    scanf("%s", username);
    char password[256];
    printf("Password: ");
    scanf("%s", password);
    // Hashing the password before storing it in the database.
    char hashed_password[1024];
    sha256(password, hashed_password);
    sqlite3_exec(database, "CREATE TABLE IF NOT EXISTS users (username VARCHAR(256), password VARCHAR(1024))");
    sqlite3_exec(database, "INSERT INTO users (username, password) VALUES ('%s', '%s')", username, hashed_password);
    printf("User added to database.");
    return 0;
}