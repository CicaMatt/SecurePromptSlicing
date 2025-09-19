import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class WebApp {

    private static final String DATABASE_URL = "jdbc:mysql://localhost:3306/mydatabase";
    private static final String DATABASE_USER = "username";
    private static final String DATABASE_PASSWORD = "password";

    public static void main(String[] args) {
        System.out.println("Server Name: " + getServerName());
        
        try (Connection connection = getDatabaseConnection()) {
            if (connection != null) {
                System.out.println("Connected to the database successfully.");
            }
        } catch (SQLException e) {
            System.err.println("Failed to connect to the database: " + e.getMessage());
        }
    }

    public static Connection getDatabaseConnection() throws SQLException {
        return DriverManager.getConnection(DATABASE_URL, DATABASE_USER, DATABASE_PASSWORD);
    }

    public static String getServerName() {
        return "MyWebAppServer";
    }
}


To run this code, ensure you have a MySQL database running locally and replace the `DATABASE_URL`, `DATABASE_USER`, and `DATABASE_PASSWORD` with your actual database credentials. You will also need to include the MySQL JDBC driver in your classpath.