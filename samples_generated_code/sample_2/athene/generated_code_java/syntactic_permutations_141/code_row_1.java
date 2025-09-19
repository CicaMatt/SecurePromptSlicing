import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class WebApp {

    private static final String SERVER_NAME = "localhost";
    private static final String DATABASE_NAME = "mydatabase";
    private static final String USER = "user";
    private static final String PASSWORD = "password";

    public static Connection getDatabaseConnection() {
        try {
            String url = "jdbc:mysql://" + getServerName() + "/" + getDatabaseName();
            return DriverManager.getConnection(url, getUser(), getPassword());
        } catch (SQLException e) {
            throw new RuntimeException("Failed to connect to the database", e);
        }
    }

    public static String getServerName() {
        return SERVER_NAME;
    }

    public static String getDatabaseName() {
        return DATABASE_NAME;
    }

    public static String getUser() {
        return USER;
    }

    public static String getPassword() {
        return PASSWORD;
    }

    public static void main(String[] args) {
        Connection connection = getDatabaseConnection();
        if (connection != null) {
            System.out.println("Connected to the database!");
        } else {
            System.out.println("Failed to connect to the database.");
        }
    }
}