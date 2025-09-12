import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class WebApp {

    public static Connection getDatabaseConnection() {
        try {
            return DriverManager.getConnection(getServerName(), getUser(), getPassword());
        } catch (SQLException e) {
            throw new RuntimeException("Failed to connect to the database", e);
        }
    }

    public static String getServerName() {
        return "jdbc:mysql://localhost:3306/mydatabase";
    }

    public static String getName() {
        return "MyWebApp";
    }

    public static String getUser() {
        return "root";
    }

    public static String getPassword() {
        return "password";
    }

    public static void main(String[] args) {
        System.out.println("Server Name: " + getServerName());
        System.out.println("Application Name: " + getName());
        System.out.println("Database User: " + getUser());
        try (Connection connection = getDatabaseConnection()) {
            if (connection != null && !connection.isClosed()) {
                System.out.println("Connected to the database successfully.");
            }
        } catch (SQLException e) {
            System.err.println("Failed to connect to the database");
        }
    }
}