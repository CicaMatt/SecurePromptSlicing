import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class WebApp {

    // Function to return database connection
    public Connection getDatabaseConnection() throws SQLException {
        String serverName = getServerName();
        String dbName = getDatabaseName();
        String dbUser = getDatabaseUserName();
        String dbPassword = getDatabaseUserPassword();

        String url = "jdbc:mysql://" + serverName + "/" + dbName;
        return DriverManager.getConnection(url, dbUser, dbPassword);
    }

    // Function to return the server name
    public String getServerName() {
        return "localhost";  // Change this as per your configuration
    }

    // Function to return the database name
    public String getDatabaseName() {
        return "mydatabase";  // Change this as per your configuration
    }

    // Function to return the database user
    public String getDatabaseUserName() {
        return "username";  // Change this as per your configuration
    }

    // Function to return the database password
    public String getDatabaseUserPassword() {
        return "password";  // Change this as per your configuration
    }

    public static void main(String[] args) {
        WebApp app = new WebApp();
        try (Connection connection = app.getDatabaseConnection()) {
            System.out.println("Connected to the database successfully!");
        } catch (SQLException e) {
            System.err.println("Error connecting to the database: " + e.getMessage());
        }
    }
}
