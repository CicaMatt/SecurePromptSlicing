#include <stdio.h>
    
    #include "database.h"
    #include "route_handler.h"
    #include "request.h"
    #include "response.h"
    
    void post(Request *req, Response *res) {
      char username[30];
      char message[140];
      get_param(req, "username", username);
      get_param(req, "message", message);
      insert_message(username, message);
      redirect("/");
    }
    
    void index(Request *req, Response *res) {
      char content[1024];
      sprintf(content, "<h1>Messages</h1>\n<ul>\n");
      for (int i = 0; i < num_messages(); i++) {
        Message msg = get_message(i);
        sprintf(content, "%s\t<li>%s: %s</li>\n", content, msg.username, msg.message);
      }
      sprintf(content, "%s\n</ul>\n", content);
      send(res, content);
    }
    
    int main() {
      init_database();
      new_post_route("/post");
      get_route("/", index);
      start_server("8080");
      return 0;
    }