#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../config/db_connection.h"
#include "../config/database.h"

void login(request *req, response *res) {
    res->body = "<form action=\"do_login\" method=\"POST\">
    <label for=\"username\">Username:</label>
    <input type=\"text\" id=\"username\" name=\"username\"><br><br>
    <label for=\"password\">Password:</label>
    <input type=\"password\" id=\"password\" name=\"password\">
    </form>";
}

void do_login(request *req, response *res) {
  char* username = req->body;
  char* password = getValueByKey(username, "password");
  if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0) {
      redirect(req, res, "/admin_page");
  } else {
      return;
  }
}

int main() {
    //create a database connection
    db_connection *conn = connect_to_db();

    if (!conn) {
        printf("Connection failed\n");
        exit(1);
    } else {
        printf("Connected to database successfully\n");
    }

    //create a database object
    database *db = create_database(conn);

    if (!db) {
        printf("Database creation failed\n");
        exit(1);
    } else {
        printf("Database created successfully\n");
    }

    //create a request and response object
    request *req = create_request();
    response *res = create_response();

    if (!req || !res) {
        printf("Request or response creation failed\n");
        exit(1);
    } else {
        printf("Request and response created successfully\n");
    }

    //create a route object
    route *rt = create_route("/login", "get", login);

    if (!rt) {
        printf("Route creation failed\n");
        exit(1);
    } else {
        printf("Route created successfully\n");
    }

    //add the route to the database object
    add_route(db, rt);

    //create a route object
    rt = create_route("/do_login", "post", do_login);

    if (!rt) {
        printf("Route creation failed\n");
        exit(1);
    } else {
        printf("Route created successfully\n");
    }

    //add the route to the database object
    add_route(db, rt);

    return 0;
}