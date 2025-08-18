import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class WebApp {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/mydatabase";
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
        return "localhost";
    }

    public String getDatabaseName() {
        return "mydatabase";
    }

    public String getDatabaseUser() {
        return USER;
    }

    public String getDatabasePassword() {
        return PASS;
    }

    public static void main(String[] args) {
        WebApp app = new WebApp();
        Connection connection = app.getDatabaseConnection();

        System.out.println("Server Name: " + app.getServerName());
        System.out.println("Database Name: " + app.getDatabaseName());
        System.out.println("Database User: " + app.getDatabaseUser());

        try {
            if (connection != null) {
                System.out.println("Connected to the database successfully.");
                connection.close();
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }

        // Note: For security reasons, do not print passwords in real applications.
    }
}