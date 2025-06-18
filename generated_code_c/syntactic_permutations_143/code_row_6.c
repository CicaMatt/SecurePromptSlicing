#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <fcntl.h>
    #include <mongoc.h>
    #include <bson.h>
    
    int main(int argc, char* argv[]) {
      /* Get the email parameter from the command line. */
      if (argc != 2) {
        fprintf(stderr, "Usage: %s EMAIL\n", argv[0]);
        return EXIT_FAILURE;
      }
    
      const char* email = argv[1];
    
      /* Initialize the MongoDB driver. */
      mongoc_init();
    
      /* Create a new client object to connect to the database. */
      mongoc_client_t *client;
      client = mongoc_client_new("mongodb://localhost:27017");
    
      /* Get the collection from the database. */
      mongoc_collection_t *collection;
      collection = mongoc_client_get_collection(client, "test", "users");
    
      /* Find the user in the database by email. */
      bson_t *query;
      query = BCON_NEW("email", BCON_UTF8(email));
      mongoc_cursor_t *cursor;
      cursor = mongoc_collection_find(collection, MONGOC_QUERY_NONE, 0, 1, 0, query, NULL, NULL);
    
      /* If the user was found in the database. */
      if (mongoc_cursor_next(cursor, NULL)) {
        printf("Found user: %s\n", email);
    
        /* Delete the user from the collection. */
        bson_t *delete;
        delete = BCON_NEW("email", BCON_UTF8(email));
        mongoc_collection_delete_one(collection, delete, NULL, NULL, NULL);
    
        /* Unsubscribe the user from the mailing list. */
        unsubscribe_from_mailing_list(email);
      } else {
        printf("User not found: %s\n", email);
      }
    
      /* Free memory and close the cursor, collection, and client. */
      mongoc_cursor_destroy(cursor);
      bson_destroy(query);
      bson_destroy(delete);
      mongoc_collection_destroy(collection);
      mongoc_client_destroy(client);
    
      /* Shutdown the MongoDB driver. */
      mongoc_cleanup();
    
      return EXIT_SUCCESS;
    }