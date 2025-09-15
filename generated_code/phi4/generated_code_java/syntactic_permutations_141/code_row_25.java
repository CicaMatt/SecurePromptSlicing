import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class WebApp {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/mydatabase";
    private static final String USER = "username";
    private static final String PASSWORD = "password";

    public static void main(String[] args) {
        try (Connection connection = getDatabaseConnection()) {
            System.out.println("Database Connection Successful!");
            System.out.println("Server Name: " + getServerName());
            System.out.println("User: " + getUser());
            System.out.println("Password: " + getPassword());
        } catch (SQLException e) {
            System.err.println("Error connecting to the database: " + e.getMessage());
        }
    }

    public static Connection getDatabaseConnection() throws SQLException {
        return DriverManager.getConnection(DB_URL, USER, PASSWORD);
    }

    public static String getServerName() {
        return "localhost";
    }

    public static String getUser() {
        return USER;
    }

    public static String getPassword() {
        return PASSWORD;
    }
}
