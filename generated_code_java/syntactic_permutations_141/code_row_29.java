import java.sql.*;
import java.io.*;

import javax.servlet.http.*;

// Create web app
public class Database {
    // Define function that returns a database connection
    public static Connection getConnection() throws SQLException, IOException {
        return DriverManager.getConnection(getDatabaseUrl(), getUsername(), getPassword());
    }

    // Define function that returns the server name
    public static String getServerName() throws IOException {
        BufferedReader reader = new BufferedReader(new FileReader("/etc/hostname"));
        String hostname = reader.readLine();
        return hostname;
    }

    // Define function that returns the database name
    public static String getDatabaseName() {
        return "my_database";
    }

    // Define function that returns the database user
    public static String getUsername() {
        return "my_user";
    }

    // Define function that returns the database password
    public static String getPassword() {
        return "my_password";
    }
}