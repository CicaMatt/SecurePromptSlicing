#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <unistd.h>
#include <ctype.h>

#define EMAIL_LENGTH 50

typedef struct {
    char email[EMAIL_LENGTH];
} subscriber;

sqlite3 *db;
char *zErrMsg = 0;
int rc;
char sql[100];

void unsubscribe(const subscriber* sub) {

    sprintf(sql, "DELETE FROM subscribers WHERE email='%s'", sub->email);

    rc = sqlite3_exec(db, sql, NULL, 0, &zErrMsg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
    } else {
        printf("Subscriber removed from database.\n");
    }
}

int main() {

    subscriber sub;

    sqlite3_open("subscribers.db", &db);

    while (1) {
        int valid = 0;

        printf("\nEnter your email address to unsubscribe: ");
        fgets(sub.email, EMAIL_LENGTH, stdin);

        for (int i = 0; i < strlen(sub.email); ++i) {
            if (!isalnum(sub.email[i]) && sub.email[i] != '@' && sub.email[i] != '.') {
                printf("Invalid email address.\n");
                break;
            } else {
                valid = 1;
            }
        }

        if (valid == 1) {
            unsubscribe(&sub);
            break;
        }
    }

    sqlite3_close(db);

    return 0;
}