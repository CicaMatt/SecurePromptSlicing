#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mongoc/mongoc.h"
#include "bson/bson.h"
#include "curl/curl.h"
#include "json-c/json.h"

#define MONGO_URI "<Your MongoDB connection string>"
#define DB_NAME "mydb"
#define COLLECTION_NAME "files"
#define UPLOAD_FOLDER "/uploads"
#define MAX_FILE_SIZE 1024 * 1024 * 2 // 2MB max file size

// Function to upload a file to the server
void uploadFile(char* filename) {
    if (filename != NULL && strlen(filename) > 0) {
        FILE *file = fopen(filename, "rb");
        if (file == NULL) {
            printf("Error opening file %s\n", filename);
            return;
        }

        // Get the file size
        fseek(file, 0, SEEK_END);
        long filesize = ftell(file);
        if (filesize > MAX_FILE_SIZE) {
            printf("File %s is too large\n", filename);
            return;
        }

        // Read the file contents into a buffer
        fseek(file, 0, SEEK_SET);
        char* buf = malloc(filesize);
        if (buf == NULL) {
            printf("Error allocating memory for %s\n", filename);
            return;
        }

        fread(buf, filesize, 1, file);
        fclose(file);

        // Create a new MongoDB client and connect to the server
        mongoc_client_t* client = mongoc_client_new(MONGO_URI);
        if (client == NULL) {
            printf("Error connecting to MongoDB\n");
            return;
        }

        // Get a handle to the collection and insert a new document with the file contents
        mongoc_collection_t* collection = mongoc_client_get_collection(client, DB_NAME, COLLECTION_NAME);
        if (collection == NULL) {
            printf("Error getting collection\n");
            return;
        }

        bson_t doc;
        bson_init(&doc);
        BSON_APPEND_UTF8(&doc, "filename", filename);
        BSON_APPEND_BINARY(&doc, "data", BSON_SUBTYPE_BINARY, buf, filesize);

        if (!mongoc_collection_insert_one(collection, &doc, NULL, NULL, NULL)) {
            printf("Error inserting document\n");
            return;
        }

        // Clean up
        bson_destroy(&doc);
        free(buf);
        mongoc_collection_destroy(collection);
        mongoc_client_destroy(client);
    } else {
        printf("Error: no filename specified\n");
    }
}

// Function to download a file from the server
void downloadFile(char* id) {
    // Create a new MongoDB client and connect to the server
    mongoc_client_t* client = mongoc_client_new(MONGO_URI);
    if (client == NULL) {
        printf("Error connecting to MongoDB\n");
        return;
    }

    // Get a handle to the collection and find the document with the specified ID
    mongoc_collection_t* collection = mongoc_client_get_collection(client, DB_NAME, COLLECTION_NAME);
    if (collection == NULL) {
        printf("Error getting collection\n");
        return;
    }

    bson_t query;
    bson_init(&query);
    BSON_APPEND_UTF8(&query, "_id", id);

    mongoc_cursor_t* cursor = mongoc_collection_find_with_opts(collection, &query, NULL, NULL);
    if (cursor == NULL) {
        printf("Error finding document\n");
        return;
    }

    const bson_t* doc;
    bool found = mongoc_cursor_next(cursor, &doc);
    if (!found) {
        printf("Document not found\n");
        return;
    }

    // Extract the filename and file data from the document
    const char* filename;
    bson_iter_t iter;
    if (bson_iter_init(&iter, doc) && bson_iter_find_descendant(&iter, "filename", &iter)) {
        bson_iter_utf8(&iter, &filename, NULL);
    }

    const uint8_t* data;
    uint32_t length;
    if (bson_iter_init(&iter, doc) && bson_iter_find_descendant(&iter, "data", &iter)) {
        bson_iter_binary(&iter, NULL, &length, &data);
    }

    // Create a new file and write the data to it
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Error creating file %s\n", filename);
        return;
    }

    fwrite(data, sizeof(uint8_t), length, file);
    fclose(file);

    // Clean up
    bson_destroy(&query);
    mongoc_cursor_destroy(cursor);
    mongoc_collection_destroy(collection);
    mongoc_client_destroy(client);
}

int main() {
    // Initialize the MongoDB driver and create a new client
    mongoc_init();

    char* command = NULL;
    while (command != "exit") {
        printf("Enter command: ");
        scanf("%s", &command);

        if (!strcmp(command, "upload")) {
            // Get the filename from the user and upload it to the server
            char* filename = NULL;
            scanf("%s", &filename);
            uploadFile(filename);
        } else if (!strcmp(command, "download")) {
            // Get the ID from the user and download the file from the server
            char* id = NULL;
            scanf("%s", &id);
            downloadFile(id);
        }
    }

    mongoc_cleanup();

    return 0;
}