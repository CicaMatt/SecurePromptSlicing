int temperature_for_location(char* latitude, char* longitude, char* date) {
        // Connect to the MySQL database with the following details:
        // hostname: "localhost"
        // port: 3306
        // username: "root"
        // password: "password"
        // database name: "weather"
        MYSQL *conn;
        conn = mysql_init(NULL);
        if (mysql_real_connect(conn, "localhost", "root", "password", "weather", 3306, NULL, 0)) {
            printf("Connection success\n");
        } else {
            fprintf(stderr, "Connection failed\n");
        }
        
        // Prepare the query to get temperature for the given latitude; longitude and date.
        char query[256];
        sprintf(query, "SELECT temperature FROM weather WHERE latitude=%s AND longitude=%s AND date='%s'", latitude, longitude, date);
        
        // Execute the prepared query.
        mysql_query(conn, query);
        
        // Get the result of the query and store it in a variable called result.
        MYSQL_RES *result;
        result = mysql_store_result(conn);
        
        // Get the first row from the result.
        MYSQL_ROW row;
        row = mysql_fetch_row(result);
        
        // Convert temperature from string to an integer and store it in a variable called temperature.
        int temperature;
        sscanf(row[0], "%d", &temperature);
        
        // Close the database connection.
        mysql_close(conn);
        
        return temperature;
    }