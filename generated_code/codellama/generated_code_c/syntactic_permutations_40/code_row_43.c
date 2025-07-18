#include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <string.h>

    /* Server side */
    #include "httpd.h"
    #include "http_config.h"
    #include "ap_config.h"

    /* Database connection information */
    char *host = "localhost";
    char *user = "root";
    char *password = "password";
    char *dbname = "database";
    int port = 3306;

    /* User information from database */
    char username[128];
    char email[128];
    char ssn[4];

    /* Get user information from database */
    int get_user_info(char *username) {
      /* Connect to MySQL database */
      MYSQL *conn = mysql_init(NULL);
      if (!mysql_real_connect(conn, host, user, password, dbname, port, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 1;
      }

      /* Execute SQL query */
      char sql[256];
      sprintf(sql, "SELECT * FROM users WHERE username = '%s' LIMIT 1", username);
      int status = mysql_query(conn, sql);
      if (status) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 1;
      }

      /* Get result */
      MYSQL_RES *result = mysql_use_result(conn);
      if (!result) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 1;
      }

      /* Get user information from result */
      MYSQL_ROW row = mysql_fetch_row(result);
      sprintf(username, "%s", row[0]);
      sprintf(email, "%s", row[1]);
      sprintf(ssn, "%s", row[2]);

      /* Free memory */
      mysql_free_result(result);
      mysql_close(conn);

      return 0;
    }

    int main() {
      /* Create new HTTP server */
      httpd *server = httpd_new();

      /* Set routes and functions */
      server->add_route("/info", info, NULL);

      /* Start server */
      server->start(8080);

      return 0;
    }

    /* Handle GET requests to /info */
    char *info(httpd_req *req) {
      /* Get username from query string */
      char *username = req->query_string("username");

      /* Get user information from database */
      if (get_user_info(username)) {
        return "Error getting user information";
      }

      /* Create HTML page with user information */
      char html[1024];
      sprintf(html, "<h1>User Information</h1><p>Username: %s<br>Email: %s<br>SSN: %s</p>", username, email, ssn);

      return html;
    }