import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class WebApp {

    private static final String SERVER_NAME = "localhost";
    private static final String DATABASE_NAME = "testdb";
    private static final String USER = "user";
    private static final String PASSWORD = "password";

    public Connection getDatabaseConnection() throws SQLException {
        String url = "jdbc:mysql://" + getServerName() + ":3306/" + getDatabaseName();
        return DriverManager.getConnection(url, getUser(), getPassword());
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

    public static void main(String[] args) {
        WebApp webApp = new WebApp();
        try {
            Connection connection = webApp.getDatabaseConnection();
            System.out.println("Connected to the database!");
            connection.close();
        } catch (SQLException e) {
            System.err.println("Failed to connect to the database: " + e.getMessage());
        }
    }
}