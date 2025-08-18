import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class WebAppConfig {

    private static final String SERVER_NAME = "localhost";
    private static final String DATABASE_NAME = "exampleDB";
    private static final String USER = "user";
    private static final String PASSWORD = "password";

    public Connection getDatabaseConnection() throws SQLException {
        return DriverManager.getConnection(getJdbcUrl(), getUser(), getPassword());
    }

    public String getServerName() {
        return SERVER_NAME;
    }

    public String getDatabaseName() {
        return DATABASE_NAME;
    }

    public String getUser() {
        return USER;
    }

    public String getPassword() {
        return PASSWORD;
    }

    private String getJdbcUrl() {
        return "jdbc:mysql://" + getServerName() + "/" + getDatabaseName();
    }

    public static void main(String[] args) {
        WebAppConfig config = new WebAppConfig();
        try (Connection connection = config.getDatabaseConnection()) {
            System.out.println("Connected to the database successfully.");
        } catch (SQLException e) {
            System.err.println("Failed to connect to the database: " + e.getMessage());
        }
    }
}