#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <sys/stat.h>
    #include <sys/types.h>
    #include <dirent.h>
    #include <fcntl.h>

    #include "mongoc.h"
    #include "bson/util.h"

    /* change the db connection string as needed */
    #define URI "mongodb://127.0.0.1:27017"
    #define DB_NAME "testdb"
    #define COLLECTION "message_board"

    void insert_user_message_in_db(char *username, char *message);

    int main() {
        /* initialize driver */
        mongoc_init();

        /* create a new client */
        mongoc_client_t *client = mongoc_client_new(URI);

        /* create a new collection */
        mongoc_collection_t *collection = mongoc_client_get_collection(client, DB_NAME, COLLECTION);

        char *username = "user1";
        char *message = "This is the message from user1.";

        /* insert data into collection */
        bson_t *doc = BCON_NEW("username", BCON_UTF8(username), "message", BCON_UTF8(message));
        bson_error_t error;
        if (!mongoc_collection_insert_one(collection, doc, NULL, NULL, &error)) {
            fprintf(stderr, "%s\n", error.message);
        }

        /* release resources */
        bson_destroy(doc);
        mongoc_collection_destroy(collection);
        mongoc_client_destroy(client);

        /* shutdown driver */
        mongoc_cleanup();

        return EXIT_SUCCESS;
    }

    void insert_user_message_in_db(char *username, char *message) {
        /* initialize driver */
        mongoc_init();

        /* create a new client */
        mongoc_client_t *client = mongoc_client_new(URI);

        /* create a new collection */
        mongoc_collection_t *collection = mongoc_client_get_collection(client, DB_NAME, COLLECTION);

        /* insert data into collection */
        bson_t *doc = BCON_NEW("username", BCON_UTF8(username), "message", BCON_UTF8(message));
        bson_error_t error;
        if (!mongoc_collection_insert_one(collection, doc, NULL, NULL, &error)) {
            fprintf(stderr, "%s\n", error.message);
        }

        /* release resources */
        bson_destroy(doc);
        mongoc_collection_destroy(collection);
        mongoc_client_destroy(client);

        /* shutdown driver */
        mongoc_cleanup();
    }