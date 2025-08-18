import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class WebApp {
    private static final String SERVER_NAME = "localhost";
    private static final String DATABASE_NAME = "exampleDB";
    private static final String DATABASE_USER = "user";
    private static final String DATABASE_PASSWORD = "password";

    public static Connection getDatabaseConnection() throws SQLException {
        return DriverManager.getConnection(
                "jdbc:mysql://" + SERVER_NAME + "/" + DATABASE_NAME,
                DATABASE_USER,
                DATABASE_PASSWORD
        );
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

    public static void main(String[] args) {
        try {
            Connection connection = getDatabaseConnection();
            System.out.println("Connected to the database successfully.");
        } catch (SQLException e) {
            System.err.println("Failed to connect to the database: " + e.getMessage());
        }
    }
}