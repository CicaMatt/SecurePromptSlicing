#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define DB_FILE "subscribers.db"

// Helper function to simulate checking if an email exists in the database
int check_email_exists(const char *email) {
    FILE *file = fopen(DB_FILE, "r");
    if (!file) return 0;

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        // Remove newline character
        line[strcspn(line, "\n")] = '\0';
        if (strcmp(line, email) == 0) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

// Helper function to simulate deleting an email from the database
void delete_email(const char *email) {
    FILE *file = fopen(DB_FILE, "r");
    if (!file) return;

    FILE *temp_file = fopen("temp.db", "w");
    if (!temp_file) {
        fclose(file);
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        // Remove newline character
        line[strcspn(line, "\n")] = '\0';
        if (strcmp(line, email) != 0) {
            fprintf(temp_file, "%s\n", line);
        }
    }

    fclose(file);
    fclose(temp_file);

    remove(DB_FILE);
    rename("temp.db", DB_FILE);
}

// Callback function for writing data received from the server
size_t write_callback(void *ptr, size_t size, size_t nmemb, void *userdata) {
    printf("%.*s", (int)(size * nmemb), (char *)ptr);
    return size * nmemb;
}

void unsubscribe_user(const char *email) {
    CURL *curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if(curl) {
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/x-www-form-urlencoded");

        char post_fields[256];
        snprintf(post_fields, sizeof(post_fields), "email=%s", email);

        curl_easy_setopt(curl, CURLOPT_URL, "http://example.com/unsubscribe");
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_fields);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);

        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <email>\n", argv[0]);
        return 1;
    }

    const char *email = argv[1];

    if (check_email_exists(email)) {
        delete_email(email);
        unsubscribe_user(email);
        printf("User unsubscribed successfully.\n");
    } else {
        printf("The user is not subscribed.\n");
    }

    return 0;
}