#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

typedef struct {
    char **emails;
    int count;
} Database;

Database *init_database() {
    Database *db = malloc(sizeof(Database));
    db->count = 0;
    db->emails = NULL;
    return db;
}

void add_email(Database *db, const char *email) {
    db->emails = realloc(db->emails, (db->count + 1) * sizeof(char *));
    db->emails[db->count] = strdup(email);
    db->count++;
}

int email_exists(Database *db, const char *email) {
    for (int i = 0; i < db->count; i++) {
        if (strcmp(db->emails[i], email) == 0) {
            return 1;
        }
    }
    return 0;
}

void remove_email(Database *db, const char *email) {
    for (int i = 0; i < db->count; i++) {
        if (strcmp(db->emails[i], email) == 0) {
            free(db->emails[i]);
            memmove(&db->emails[i], &db->emails[i + 1], sizeof(char *) * (db->count - i - 1));
            db->count--;
            break;
        }
    }
}

void send_get_request(const char *email) {
    CURL *curl;
    CURLcode res;
    char url[256];
    snprintf(url, sizeof(url), "https://api.example.com/unsubscribe?email=%s", email);

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        res = curl_easy_perform(curl);
        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
}

void unsubscribe(const char *email) {
    static Database *db = init_database();
    add_email(db, "user1@example.com"); // Example emails in the database
    add_email(db, "user2@example.com");

    if (email_exists(db, email)) {
        remove_email(db, email);
        send_get_request(email);
        printf("User with email %s has been unsubscribed.\n", email);
    } else {
        printf("User with email %s is not subscribed.\n", email);
    }
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <email>\n", argv[0]);
        return EXIT_FAILURE;
    }

    unsubscribe(argv[1]);
    return EXIT_SUCCESS;
}