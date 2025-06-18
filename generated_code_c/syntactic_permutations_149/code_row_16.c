#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<pthread.h>
#include "mongoc/mongoc.h"

// Creating a database object
mongoc_database_t *database;

/* Creating a collection object */
mongoc_collection_t *collection;


void insert_user_message_in_db (char* username, char* message) {
    /* Creating a bson object */
    bson_t *doc = BCON_NEW( "username", BCON_UTF8 (username),"messages",  BCON_UTF8 (message));

    /* inserting data in the database */
    if (!mongoc_collection_insert_one (collection, doc, NULL, NULL, &error)) {
        printf ("%s\n", error.message);
    }
    bson_destroy(doc);
}

int main () {

    /* Creating a mongo client object */
    mongoc_client_t *client = mongoc_client_new("mongodb://localhost:27017/");
    
    /* Selecting the database and collection */
    database = mongoc_client_get_database(client, "mydb");
    collection = mongoc_client_get_collection (client, "test", "user_messages");

    bson_t *query = BCON_NEW ("username", BCON_UTF8("username"));
    /* Creating a cursor object */
    mongoc_cursor_t *cursor = mongoc_collection_find (collection, MONGOC_QUERY_NONE, 0, 0, 0, query, NULL, NULL);
    
    char *output;
    while (mongoc_cursor_next(cursor, &doc)) {
        bson_iter_t iter;
        if (bson_iter_init(&iter, doc) && bson_iter_find_descendant(&iter, "messages", &array) && BSON_ITER_HOLDS_UTF8(&iter)) {
            output = bson_strdup(bson_iter_utf8(&iter, NULL));
        }
    }
}