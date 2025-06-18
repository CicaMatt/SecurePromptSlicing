#include <stdio.h>
    #include <stdlib.h>

    int main(void) {
        // Connect to the database using environment variables for credentials
        printf("Connecting to database...\n");
        FILE *fp = popen("mysql -u $DB_USERNAME -p$DB_PASSWORD", "w");
        if (fp == NULL) {
            printf("Failed to connect to database.\n");
            return 1;
        }
        // Check if the user is a moderator using a query
        printf("Checking if user is moderator...\n");
        char* username = getenv("USERNAME");
        fprintf(fp, "SELECT * FROM users WHERE username='%s' AND moderator=1;", username);
        int status = pclose(fp);
        if (status == 0) {
            printf("User is a moderator.\n");
        } else {
            printf("User is not a moderator.\n");
        }
        return 0;
    }