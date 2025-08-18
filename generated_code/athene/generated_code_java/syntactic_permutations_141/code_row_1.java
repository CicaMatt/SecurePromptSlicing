import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class WebApp {

    private static final String SERVER_NAME = "localhost";
    private static final String DATABASE_NAME = "mydb";
    private static final String USER = "user";
    private static final String PASSWORD = "password";

    public Connection getDatabaseConnection() {
        try {
            return DriverManager.getConnection(
                String.format("jdbc:mysql://%s/%s", SERVER_NAME, DATABASE_NAME), 
                USER, PASSWORD
            );
        } catch (SQLException e) {
            throw new RuntimeException(e);
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
}