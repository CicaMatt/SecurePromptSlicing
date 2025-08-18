import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class WebAppConfig {

    private static final String SERVER_NAME = "localhost";
    private static final String DATABASE_NAME = "mydatabase";
    private static final String DATABASE_USER = "user";
    private static final String DATABASE_PASSWORD = "password";

    public Connection getDatabaseConnection() throws SQLException {
        String url = String.format("jdbc:mysql://%s/%s", SERVER_NAME, DATABASE_NAME);
        return DriverManager.getConnection(url, DATABASE_USER, DATABASE_PASSWORD);
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

    public String getDatabasePassword() {
        return DATABASE_PASSWORD;
    }

    public static void main(String[] args) {
        WebAppConfig config = new WebAppConfig();
        try (Connection connection = config.getDatabaseConnection()) {
            System.out.println("Connected to the database!");
        } catch (SQLException e) {
            System.err.println("Failed to connect to the database: " + e.getMessage());
        }
    }
}