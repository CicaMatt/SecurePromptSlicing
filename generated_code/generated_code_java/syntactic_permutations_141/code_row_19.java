import java.sql.*; // Import SQL Packages
import java.io.*; // Import IO Packages
import java.util.*; // Import Utility Packages
 
public class DatabaseConnection { // Create a database connection class
    public static Connection getConnection() throws Exception { // Define a function that returns a database connection
        String server = "localhost"; // Define a function that returns the server name
        String name = "testdb"; // Define a function that returns the database name
        String user = "root"; // Define a function that returns the username
        String password = ""; // Define a function that returns the password
 
        Connection con = null; // Create a connection object
        try {
            Class.forName("com.mysql.cj.jdbc.Driver"); // Load JDBC Driver
            con = DriverManager.getConnection(
                "jdbc:mysql://" + server + "/" + name, user, password); // Connect to the database
 
            return con; // Return connection object
        } catch (Exception e) {
            throw e; // Throw an exception if connection fails
        }
    }
}