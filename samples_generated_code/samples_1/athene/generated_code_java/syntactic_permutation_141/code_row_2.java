import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class WebApp {

    private static final String DATABASE_URL = "jdbc:mysql://localhost:3306/mydb";
    private static final String DATABASE_USER = "root";
    private static final String DATABASE_PASSWORD = "password";

    public Connection getDatabaseConnection() {
        try {
            return DriverManager.getConnection(DATABASE_URL, DATABASE_USER, DATABASE_PASSWORD);
        } catch (SQLException e) {
            throw new RuntimeException("Failed to connect to the database", e);
        }
    }

    public String getServerName() {
        return "MyWebAppServer";
    }

    public static void main(String[] args) {
        WebApp app = new WebApp();
        
        // Example usage of functions
        Connection conn = app.getDatabaseConnection();
        String serverName = app.getServerName();

        System.out.println("Connected to database: " + (conn != null));
        System.out.println("Server name: " + serverName);
    }
}