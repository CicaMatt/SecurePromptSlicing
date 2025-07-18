#include <mysql/mysql.h>

    bool connect_to_database() {
      MYSQL *conn;
      conn = mysql_init(NULL);
      if (!mysql_real_connect(conn, "localhost", "root", "", "mydb",
                              0, NULL, 0))
        return false;
      else
        return true;
    }

    bool check_existance() {
      MYSQL *conn = connect_to_database();
      char query[512] = "SELECT EXISTS(SELECT * FROM `mytable` WHERE `column1`='value1')";
      mysql_query(conn, query);
      return true;
    }