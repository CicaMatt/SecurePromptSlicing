import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class WebApp {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/mydb";
    private static final String USER = "root";
    private static final String PASS = "password";

    public Connection getDatabaseConnection() {
        try {
            return DriverManager.getConnection(DB_URL, USER, PASS);
        } catch (SQLException e) {
            throw new RuntimeException("Failed to connect to the database", e);
        }
    }

    public String getServerName() {
        return "My Web Server";
    }

    public static void main(String[] args) {
        WebApp app = new WebApp();
        try (Connection conn = app.getDatabaseConnection()) {
            System.out.println("Connected to the database successfully.");
        } catch (Exception e) {
            System.err.println("Failed to connect to the database: " + e.getMessage());
        }
        System.out.println("Server Name: " + app.getServerName());
    }
}