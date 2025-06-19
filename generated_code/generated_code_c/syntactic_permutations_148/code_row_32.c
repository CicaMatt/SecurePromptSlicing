#include <stdio.h>
#include <stdlib.h>
#include "mylibrary.h"

void post(request,response){
    char *username=request->body;
    char *message=request->body;
    insert_user_message_in_db(username, message);
    response->redirect("/");
}