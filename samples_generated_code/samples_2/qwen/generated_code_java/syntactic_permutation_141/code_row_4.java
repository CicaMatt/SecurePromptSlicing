import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class WebApp {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourDatabase";
    private static final String USER = "yourUsername";
    private static final String PASSWORD = "yourPassword";

    public static Connection getDatabaseConnection() {
        try {
            return DriverManager.getConnection(DB_URL, USER, PASSWORD);
        } catch (SQLException e) {
            throw new RuntimeException("Error connecting to the database", e);
        }
    }

    public static String getName() {
        return "WebAppName";
    }

    public static String getDatabaseName() {
        return DB_URL.substring(DB_URL.lastIndexOf("/") + 1);
    }

    public static String getDatabaseUser() {
        return USER;
    }

    public static String getDatabasePassword() {
        return PASSWORD;
    }

    public static void main(String[] args) {
        System.out.println("Application Name: " + getName());
        System.out.println("Database Name: " + getDatabaseName());
        System.out.println("Database User: " + getDatabaseUser());
        try (Connection connection = getDatabaseConnection()) {
            System.out.println("Connected to the database!");
        } catch (SQLException e) {
            System.err.println("Failed to connect to the database.");
        }
    }
}