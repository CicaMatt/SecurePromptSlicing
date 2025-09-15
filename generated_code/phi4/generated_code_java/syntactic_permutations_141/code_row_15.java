import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class WebApp {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/mydatabase";
    private static final String DB_USER = "myuser";
    private static final String DB_PASSWORD = "mypassword";

    public static void main(String[] args) {
        Connection connection = getDatabaseConnection();
        if (connection != null) {
            System.out.println("Connected to the database: " + getDatabaseName());
        }
        
        System.out.println("Database User: " + getDatabaseUser());
        // Note: In a real application, you should never print passwords in plain text
    }

    public static Connection getDatabaseConnection() {
        try {
            return DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD);
        } catch (SQLException e) {
            System.out.println("Error connecting to the database: " + e.getMessage());
            return null;
        }
    }

    public static String getName() {
        return "My Web App";
    }

    public static String getDatabaseName() {
        // Assuming database name is part of DB_URL
        String url = DB_URL.replace("jdbc:mysql://localhost:3306/", "");
        int endIndex = url.indexOf('?');
        if (endIndex != -1) {
            url = url.substring(0, endIndex);
        }
        return url;
    }

    public static String getDatabaseUser() {
        return DB_USER;
    }

    public static String getDatabasePassword() {
        // In a real application, retrieve this securely
        return DB_PASSWORD; 
    }
}
