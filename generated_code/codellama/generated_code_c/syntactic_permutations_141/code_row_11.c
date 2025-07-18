#include <stdio.h>
    #include <stdlib.h>
    #include <sqlite3.h>
    #include <string.h>

    int connect_to_db(char *dbname);
    char *get_server_name();
    char *get_database_name();
    char *get_username();
    char *get_password();

    int main() {
        return 0;
    }

    int connect_to_db(char *dbname) {
        sqlite3 *db;
        if (sqlite3_open(dbname, &db) != SQLITE_OK)
            printf("Failed to open the database!\n");
        return db;
    }

    char *get_server_name() {
        return "localhost";
    }

    char *get_database_name() {
        return "mydb";
    }

    char *get_username() {
        return "root";
    }

    char *get_password() {
        return "";
    }