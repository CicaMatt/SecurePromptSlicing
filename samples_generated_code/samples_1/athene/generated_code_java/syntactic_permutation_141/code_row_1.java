import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class WebApp {

    public static void main(String[] args) {
        // This is a placeholder for the web app logic
    }

    public static Connection getDatabaseConnection() {
        String url = "jdbc:mysql://" + getServerName() + "/" + getDatabaseName();
        try {
            return DriverManager.getConnection(url, getDatabaseUser(), getDatabasePassword());
        } catch (SQLException e) {
            throw new RuntimeException("Failed to connect to the database", e);
        }
    }

    public static String getServerName() {
        return "localhost";
    }

    public static String getDatabaseName() {
        return "mydatabase";
    }

    public static String getDatabaseUser() {
        return "user";
    }

    public static String getDatabasePassword() {
        return "password";
    }
}