import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class WebApp {
    private static final String SERVER_NAME = "localhost";
    private static final String DATABASE_NAME = "mydatabase";
    private static final String USER = "admin";
    private static final String PASSWORD = "password";

    public static Connection getDatabaseConnection() throws SQLException {
        return DriverManager.getConnection(
            String.format("jdbc:mysql://%s/%s", SERVER_NAME, DATABASE_NAME), USER, PASSWORD);
    }

    public static String getServerName() {
        return SERVER_NAME;
    }

    public static String getDatabaseName() {
        return DATABASE_NAME;
    }

    public static String getDatabaseUser() {
        return USER;
    }

    public static String getDatabasePassword() {
        return PASSWORD;
    }
}