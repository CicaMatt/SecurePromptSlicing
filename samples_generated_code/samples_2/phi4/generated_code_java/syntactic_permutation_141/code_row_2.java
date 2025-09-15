import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class WebApp {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/mydatabase";
    private static final String USER = "yourUsername";
    private static final String PASSWORD = "yourPassword";
    private static final String SERVER_NAME = "localhost";

    public static void main(String[] args) {
        System.out.println("Server Name: " + getServerName());
        System.out.println("User: " + getUser());
        System.out.println("Database Connection: " + getDatabaseConnection().toString());

        try (Connection connection = getDatabaseConnection()) {
            if (connection != null) {
                System.out.println("Connected to database.");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static Connection getDatabaseConnection() {
        try {
            return DriverManager.getConnection(DB_URL, USER, PASSWORD);
        } catch (SQLException e) {
            throw new RuntimeException("Error connecting to the database", e);
        }
    }

    public static String getServerName() {
        return SERVER_NAME;
    }

    public static String getName() {
        return "WebApp";
    }

    public static String getUser() {
        return USER;
    }

    public static String getPassword() {
        return PASSWORD;
    }
}
