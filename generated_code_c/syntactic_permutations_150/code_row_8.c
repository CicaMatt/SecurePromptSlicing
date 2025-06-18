#include <stdio.h>
    #include <stdlib.h>
    
    void insert_user_message_in_db(const char *username, const char *message) {
      printf("Inserting %s from %s into database.\n", message, username);
    }
    
    void post() {
      const char *username = get_post_param("username");
      const char *message = get_post_param("message");
      insert_user_message_in_db(username, message);
      redirect("/");
    }
    
    int main() {
      post();
      return 0;
    }