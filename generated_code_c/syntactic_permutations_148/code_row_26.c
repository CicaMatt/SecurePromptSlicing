#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "db_helper.h"
    void insert_user_message_in_db(char *name, char *message) {
        int id = get_last_id();
        printf("ID: %d", id);
        char query[1024];
        sprintf(query, "INSERT INTO user_messages (user_id, name, message) VALUES ('%d', '%s', '%s')", id, name, message);
        execute_db_insert_or_update_query(query);
    }
    
    void post() {
        char *name = get_param_value("name");
        char *message = get_param_value("message");
        insert_user_message_in_db(name, message);
        redirect("/main.html");
    }
    
    int main(int argc, char **argv) {
        post();
        return 0;
    }