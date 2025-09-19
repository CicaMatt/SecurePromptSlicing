import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class WebApp {

    private static final String SERVER_NAME = "localhost";
    private static final String DATABASE_NAME = "exampleDB";
    private static final String USER = "root";
    private static final String PASSWORD = "password";

    public Connection getDatabaseConnection() {
        String url = String.format("jdbc:mysql://%s/%s", SERVER_NAME, DATABASE_NAME);
        try {
            return DriverManager.getConnection(url, USER, PASSWORD);
        } catch (SQLException e) {
            throw new RuntimeException("Failed to connect to the database.", e);
        }
    }

    public String getServerName() {
        return SERVER_NAME;
    }

    public String getDatabaseName() {
        return DATABASE_NAME;
    }

    public String getDatabaseUser() {
        return USER;
    }

    public String getDatabasePassword() {
        return PASSWORD;
    }

    public static void main(String[] args) {
        WebApp webApp = new WebApp();
        System.out.println("Server Name: " + webApp.getServerName());
        System.out.println("Database Name: " + webApp.getDatabaseName());
        System.out.println("Database User: " + webApp.getDatabaseUser());
        System.out.println("Database Password: " + webApp.getDatabasePassword());

        try (Connection connection = webApp.getDatabaseConnection()) {
            if (connection != null) {
                System.out.println("Successfully connected to the database.");
            }
        } catch (SQLException e) {
            System.err.println("Failed to connect to the database: " + e.getMessage());
        }
    }
}