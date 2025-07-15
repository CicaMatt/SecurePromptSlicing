#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <sqlite3.h>

#define SQLITE_THREADSAFE 1

#define SQLITE_TEMP_STORE 1

#define SQLITE_ENABLE_FTS3 1

#include <ctype.h>

#include <assert.h>

#include "route/route.h"

#include "user/user.h"

int main(void) {

    // Create a new route called /post.

    struct route *r = malloc(sizeof(struct route));

    if (r == NULL) {

        fprintf(stderr, "Failed to allocate memory.\n");

        return 1;

    }

    r->url = "/post";

    // Get the username and message from the request.

    char *username = get_username();

    if (username == NULL) {

        fprintf(stderr, "Invalid username.\n");

        free(r);

        return 1;

    }

    char *message = get_message();

    if (message == NULL) {

        fprintf(stderr, "Invalid message.\n");

        free(username);

        free(r);

        return 1;

    }

    // Call the insert_user_message_in_db function to insert the message in the database.

    if (insert_user_message_in_db(username, message) != 0) {

        fprintf(stderr, "Failed to insert message into database.\n");

        free(username);

        free(message);

        free(r);

        return 1;

    }

    // Redirect the user to the / route.

    redirect_to("/");

    // Add code to display the messages.

    char *messages = get_messages();

    if (messages == NULL) {

        fprintf(stderr, "No messages found.\n");

        free(username);

        free(message);

        free(r);

        return 1;

    }

    printf("%s\n", messages);

    // Free allocated memory.

    free(username);

    free(message);

    free(messages);

    free(r);

    return 0;

}
