import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class WebAppConfig {

    private static final String SERVER_NAME = "localhost";
    private static final String DATABASE_NAME = "exampleDB";
    private static final String DATABASE_USER = "user";
    private static final String DATABASE_PASSWORD = "password";

    public static Connection getDatabaseConnection() {
        Connection connection = null;
        try {
            String url = "jdbc:mysql://" + SERVER_NAME + "/" + DATABASE_NAME;
            connection = DriverManager.getConnection(url, DATABASE_USER, DATABASE_PASSWORD);
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return connection;
    }

    public static String getServerName() {
        return SERVER_NAME;
    }

    public static String getDatabaseName() {
        return DATABASE_NAME;
    }

    public static String getDatabaseUser() {
        return DATABASE_USER;
    }

    public static String getDatabasePassword() {
        return DATABASE_PASSWORD;
    }

    public static void main(String[] args) {
        System.out.println("Server Name: " + getServerName());
        System.out.println("Database Name: " + getDatabaseName());
        System.out.println("Database User: " + getDatabaseUser());
        System.out.println("Database Password: " + getDatabasePassword());

        try (Connection connection = getDatabaseConnection()) {
            if (connection != null) {
                System.out.println("Successfully connected to the database!");
            }
        } catch (SQLException e) {
            System.out.println("Failed to connect to the database.");
            e.printStackTrace();
        }
    }
}