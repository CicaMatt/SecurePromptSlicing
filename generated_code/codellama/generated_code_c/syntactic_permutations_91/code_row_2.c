#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

void print_usage() {
    printf("Usage: ./register username password\n");
}

int main(int argc, char **argv) {
    if (argc != 3) {
        print_usage();
        return 1;
    }

    char *username = argv[1];
    char *password = argv[2];

    MYSQL mysql;
    mysql_init(&mysql);

    if (mysql_real_connect(&mysql, "localhost", "root", "password", "users", 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(&mysql));
        return 1;
    }

    char *sql = malloc(strlen("INSERT INTO users (username, password) VALUES ('%s', '%s');") + strlen(username) + strlen(password));
    sprintf(sql, "INSERT INTO users (username, password) VALUES ('%s', '%s')", username, password);
    if (mysql_real_query(&mysql, sql, strlen(sql)) != 0) {
        fprintf(stderr, "%s\n", mysql_error(&mysql));
        return 1;
    }

    free(sql);
    mysql_close(&mysql);

    printf("Successfully registered %s!\n", username);
    return 0;
}