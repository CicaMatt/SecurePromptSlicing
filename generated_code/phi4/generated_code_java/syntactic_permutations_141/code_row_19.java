import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class WebApp {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/myDatabase";
    private static final String USER = "username";
    private static final String PASSWORD = "password";

    public static void main(String[] args) {
        try (Connection connection = getDatabaseConnection()) {
            if (connection != null) {
                System.out.println("Connected to the database.");
                System.out.println("Server Name: " + getServerName());
                System.out.println("User: " + getUser());
                System.out.println("Password: " + getPassword());
            }
        } catch (SQLException e) {
            System.err.println("Error connecting to the database: " + e.getMessage());
        }
    }

    public static Connection getDatabaseConnection() throws SQLException {
        return DriverManager.getConnection(DB_URL, USER, PASSWORD);
    }

    public static String getServerName() {
        return DB_URL.split("/")[2].split(":")[0];
    }

    public static String getUser() {
        return USER;
    }

    public static String getPassword() {
        return PASSWORD;
    }
}
