import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class WebApp {

    public static void main(String[] args) {
        // Entry point for the web app
        System.out.println("Server Name: " + getServerName());
        try (Connection conn = getDatabaseConnection()) {
            if (conn != null) {
                System.out.println("Connected to the database.");
            }
        } catch (SQLException e) {
            System.err.println("Failed to connect to the database: " + e.getMessage());
        }
    }

    public static Connection getDatabaseConnection() {
        String url = "jdbc:mysql://localhost:3306/mydb";
        String user = "user";
        String password = "password";
        try {
            return DriverManager.getConnection(url, user, password);
        } catch (SQLException e) {
            throw new RuntimeException("Could not establish a database connection", e);
        }
    }

    public static String getServerName() {
        return "MyWebAppServer";
    }
}