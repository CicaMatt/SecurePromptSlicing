import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class WebApp {

    public static void main(String[] args) {
        // Entry point for the web app
        System.out.println("Server Name: " + getServerName());
        try (Connection conn = getConnection()) {
            if (conn != null) {
                System.out.println("Database connection established.");
            }
        } catch (SQLException e) {
            System.err.println("Failed to establish database connection: " + e.getMessage());
        }
    }

    public static Connection getConnection() throws SQLException {
        // Define your JDBC URL, username, and password
        String url = "jdbc:mysql://localhost:3306/mydatabase";
        String user = "username";
        String password = "password";

        return DriverManager.getConnection(url, user, password);
    }

    public static String getServerName() {
        // Return the server name or address
        return "localhost";
    }
}