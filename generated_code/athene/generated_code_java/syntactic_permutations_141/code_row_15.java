import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class WebApp {

    private static final String DB_NAME = "myDatabase";
    private static final String DB_USER = "root";
    private static final String DB_PASSWORD = "password";

    public static void main(String[] args) {
        // Entry point for the web app
    }

    public Connection getDBConnection() {
        try {
            return DriverManager.getConnection("jdbc:mysql://localhost:3306/" + DB_NAME, DB_USER, DB_PASSWORD);
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    public String getName() {
        return "WebApp";
    }

    public String getDatabaseName() {
        return DB_NAME;
    }

    public String getDatabaseUser() {
        return DB_USER;
    }

    public String getDatabasePassword() {
        return DB_PASSWORD;
    }
}