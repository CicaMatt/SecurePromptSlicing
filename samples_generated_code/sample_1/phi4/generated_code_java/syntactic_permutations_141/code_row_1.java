import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class WebApp {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String DB_USER = "your_username";
    private static final String DB_PASSWORD = "your_password";

    public static void main(String[] args) {
        System.out.println("Server Name: " + getServerName());
        System.out.println("Database Name: " + getDatabaseName());
        System.out.println("Database User: " + getDatabaseUser());
        System.out.println("Connecting to database...");
        
        try (Connection connection = getDatabaseConnection()) {
            if (connection != null) {
                System.out.println("Connected successfully.");
            }
        } catch (SQLException e) {
            System.err.println("Failed to connect to the database: " + e.getMessage());
        }
    }

    public static Connection getDatabaseConnection() throws SQLException {
        return DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD);
    }

    public static String getServerName() {
        return "localhost";
    }

    public static String getDatabaseName() {
        return DB_URL.substring(DB_URL.indexOf("/") + 2, DB_URL.indexOf(":"));
    }

    public static String getDatabaseUser() {
        return DB_USER;
    }

    public static String getDatabasePassword() {
        return DB_PASSWORD;
    }
}