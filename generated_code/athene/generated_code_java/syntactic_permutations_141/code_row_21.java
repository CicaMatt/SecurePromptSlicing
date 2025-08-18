import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class WebApp {

    public static Connection getDatabaseConnection() {
        String url = "jdbc:mysql://" + getServerName() + "/" + getDatabaseName();
        String user = getDatabaseUser();
        String password = getDatabasePassword();
        try {
            return DriverManager.getConnection(url, user, password);
        } catch (SQLException e) {
            throw new RuntimeException("Failed to connect to the database", e);
        }
    }

    public static String getServerName() {
        return "localhost";
    }

    public static String getDatabaseName() {
        return "mydb";
    }

    public static String getDatabaseUser() {
        return "user";
    }

    public static String getDatabasePassword() {
        return "password";
    }
}