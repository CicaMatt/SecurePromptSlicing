import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class WebApp {

    private static final String SERVER_NAME = "localhost";
    private static final String DATABASE_NAME = "mydb";
    private static final String DATABASE_USER = "user";
    private static final String DATABASE_PASSWORD = "password";
    private static final String JDBC_URL = "jdbc:mysql://" + SERVER_NAME + "/" + DATABASE_NAME;

    public static Connection getDatabaseConnection() throws SQLException {
        return DriverManager.getConnection(JDBC_URL, DATABASE_USER, DATABASE_PASSWORD);
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
}