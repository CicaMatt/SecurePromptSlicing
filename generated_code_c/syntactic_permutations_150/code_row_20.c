#include <stdio.h>
#include "main.h"
void post(Request *request, Response *response){
    insert_user_message_in_db(request->form_data["message"]);
    redirect("/", response);
}