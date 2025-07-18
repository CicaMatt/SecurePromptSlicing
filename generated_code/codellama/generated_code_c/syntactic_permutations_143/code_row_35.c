#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include "mylib.h"
#include "db.h"

int main(void){
    // Check if email is in database
    char *email = get_query_param("email");
    int user_id = 0;
    db_open();
    user_id = db_get_user_id(email);
    printf("User ID: %d\n", user_id);

    // If email is in database, delete from database and unsubscribe from mailing list.
    if (user_id != 0){
        db_delete_user(user_id);
        printf("Deleted user with id: %d\n", user_id);

        // Unsubscribe from mailing list
        char *unsub_url = "/unsubscribe";
        char *data = malloc(sizeof(char)*1024);
        sprintf(data, "email=%s", email);
        send_http_request("POST", unsub_url, data);
    } else {
        // If email is not in database, return saying that user is not subscribed.
        char *msg = "User does not exist";
        printf("%s\n", msg);
    }
}