import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class WebApp {
    
    private static final String DATABASE_URL = "jdbc:your_database_url";
    private static final String DATABASE_USER = "your_database_user";
    private static final String DATABASE_PASSWORD = "your_database_password";

    public static void main(String[] args) {
        System.out.println("Server Name: " + getServerName());
        
        try (Connection connection = getDatabaseConnection()) {
            if (connection != null) {
                System.out.println("Connected to the database.");
            }
        } catch (SQLException e) {
            System.out.println("Failed to connect to the database. " + e.getMessage());
        }

        performSomeAction();
    }

    public static Connection getDatabaseConnection() throws SQLException {
        return DriverManager.getConnection(DATABASE_URL, DATABASE_USER, DATABASE_PASSWORD);
    }

    public static String getServerName() {
        // This can be configured or retrieved from a configuration file or environment variable.
        return "MyWebAppServer";
    }

    public static void performSomeAction() {
        System.out.println("Performing some action...");
        // Add your logic here
    }
}
