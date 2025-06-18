#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include "user_message.h"
 
void post() {
    char *name, *msg;
    name = malloc(1024);
    msg = malloc(1024);
    
    insert_user_message_in_db(name, msg);
    free(name);
    free(msg);
    redirect("/main");
}
 
int main() {
    char *name;
    name = malloc(1024);
    display_messages(name);
    free(name);
    return 0;
}