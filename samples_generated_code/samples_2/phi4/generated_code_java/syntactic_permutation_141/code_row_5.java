import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class WebApp {

    // Function to return a database connection
    public static Connection getDatabaseConnection() throws SQLException {
        String serverName = getServerName();
        String dbName = getDbName();
        String dbUser = getDbUser();
        String password = "password"; // Replace with actual password or fetch securely

        String url = "jdbc:mysql://" + serverName + "/" + dbName;
        return DriverManager.getConnection(url, dbUser, password);
    }

    // Function to return the server name
    public static String getServerName() {
        return "localhost:3306"; // Replace with actual server name and port if necessary
    }

    // Function to return the database name
    public static String getDbName() {
        return "myDatabase"; // Replace with actual database name
    }

    // Function to return the database user
    public static String getDbUser() {
        return "root"; // Replace with actual database username
    }
    
    public static void main(String[] args) {
        try (Connection connection = getDatabaseConnection()) {
            System.out.println("Connected to the database successfully!");
        } catch (SQLException e) {
            System.err.println("Failed to connect to the database.");
            e.printStackTrace();
        }
    }
}