import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class WebApp {

    private static final String SERVER_NAME = "localhost";
    private static final String DATABASE_NAME = "mydatabase";
    private static final String DATABASE_USER = "user";
    private static final String DATABASE_PASSWORD = "password";

    public Connection getDatabaseConnection() throws SQLException {
        return DriverManager.getConnection(
            String.format("jdbc:mysql://%s/%s", SERVER_NAME, DATABASE_NAME),
            DATABASE_USER,
            DATABASE_PASSWORD
        );
    }

    public String getServerName() {
        return SERVER_NAME;
    }

    public String getDatabaseName() {
        return DATABASE_NAME;
    }

    public String getDatabaseUser() {
        return DATABASE_USER;
    }
}