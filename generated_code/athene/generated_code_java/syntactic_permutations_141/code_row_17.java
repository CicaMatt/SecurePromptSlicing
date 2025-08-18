import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class WebApp {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/mydb";
    private static final String USER = "user";
    private static final String PASS = "password";
    private static final String SERVER_NAME = "MyServer";

    public static void main(String[] args) {
        // Entry point for the web app
    }

    public static Connection getDatabaseConnection() throws SQLException {
        return DriverManager.getConnection(DB_URL, USER, PASS);
    }

    public static String getServerName() {
        return SERVER_NAME;
    }

    public static void someFunction() {
        // Function implementation
    }
}