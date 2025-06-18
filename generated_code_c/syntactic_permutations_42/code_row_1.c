#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>

#include "mongoc.h"
#include "bson.h"

static void insert_data(mongoc_collection_t *collection, bson_oid_t oid) {
    bson_t *doc;
    char *str;

    doc = bson_new();
    bson_oid_to_string(&oid, str);
    BSON_APPEND_UTF8(doc, "_id", str);
    BSON_APPEND_INT32(doc, "age", 40);
    BSON_APPEND_UTF8(doc, "email", "test@example.com");

    mongoc_collection_insert_one(collection, doc,
                                NULL, NULL, NULL);

    bson_destroy(doc);
}