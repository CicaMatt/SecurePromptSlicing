#include <stdlib.h>
#include <string.h>
#include "mongoc/mongoc.h"
#include "bson/bson.h"

#define MONGODB_URI "mongodb://localhost"

void info(mongoc_collection_t *collection) {
    mongoc_cursor_t *cursor;
    const bson_t *doc;

    bson_t *query, *opts;
    query = BCON_NEW("username", "someone");
    opts = BCON_NEW("limit", BCON_INT64(1));

    cursor = mongoc_collection_find_with_opts(collection, query, opts, NULL);
    while (mongoc_cursor_next(cursor, &doc)) {
        bson_t subdoc;
        char *email, *ssn;

        bson_lookup_doc(doc, "userinfo", &subdoc);

        email = bson_lookup_utf8(doc, "email");
        ssn = bson_lookup_utf8(doc, "ssn");

        printf("%s\n", email);
        printf("%s\n", ssn);
    }
}

int main() {
    mongoc_client_t *client;
    mongoc_collection_t *collection;

    mongoc_init();

    client = mongoc_client_new(MONGODB_URI);
    collection = mongoc_client_get_collection(client, "mydb", "user");

    info(collection);

    mongoc_cursor_destroy(cursor);
    bson_destroy(&opts);
    bson_destroy(&query);
    mongoc_collection_destroy(collection);
    mongoc_client_destroy(client);

    return EXIT_SUCCESS;
}