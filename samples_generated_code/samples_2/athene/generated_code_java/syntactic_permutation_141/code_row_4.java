import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class WebApp {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/mydatabase";
    private static final String DB_NAME = "mydatabase";
    private static final String DB_USER = "user";
    private static final String DB_PASSWORD = "password";

    public static void main(String[] args) {
        // Entry point for the web app
    }

    public static Connection getDatabaseConnection() {
        try {
            return DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD);
        } catch (SQLException e) {
            throw new RuntimeException("Failed to connect to the database", e);
        }
    }

    public String getName() {
        return "WebApp";
    }

    public static String getDatabaseName() {
        return DB_NAME;
    }

    public static String getDatabaseUser() {
        return DB_USER;
    }

    public static String getDatabasePassword() {
        return DB_PASSWORD;
    }
}