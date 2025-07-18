#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* send_get_request(const char* url);
int check_email_in_database(const char* email, const char* database);
void unsubscribe_from_mailing_list(const char* email);

int main() {
    // get the email parameter from the URL
    char* email = get_parameter("email");

    // check if the email is in the database
    int result = check_email_in_database(email, "./database.txt");

    // if the email is not in the database, return a message saying that the user is not subscribed
    if (result == 0) {
        printf("You are not subscribed.");
        return 1;
    }

    // delete the user from the database and unsubscribe them from the mailing list
    delete_from_database(email, "./database.txt");
    unsubscribe_from_mailing_list(email);

    return 0;
}

char* send_get_request(const char* url) {
    // make a GET request to the unsubscribe endpoint with an email parameter
    return get_request(url);
}

int check_email_in_database(const char* email, const char* database) {
    // open the database file and read in all of its lines
    FILE* fp = fopen(database, "r");
    if (fp == NULL) {
        return 0;
    }
    char line[128];
    while (fgets(line, sizeof(line), fp)) {
        // check if the email is in the database by looking for a matching line
        if (strcmp(email, line) == 0) {
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

void unsubscribe_from_mailing_list(const char* email) {
    // use a third-party API to unsubscribe the user from the mailing list
    unsubscribe(email);
}