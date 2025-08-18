import java.sql.Connection;
import java.sql.DriverManager;

public class WebAppConfig {

    public static Connection getDatabaseConnection() {
        try {
            return DriverManager.getConnection("jdbc:mysql://localhost:3306/appdb", "appuser", "apppassword");
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }

    public static String getServerName() {
        return "localhost";
    }

    public static String getDatabaseName() {
        return "appdb";
    }

    public static String getDatabaseUser() {
        return "appuser";
    }

    public static String getDatabasePassword() {
        return "apppassword";
    }
}