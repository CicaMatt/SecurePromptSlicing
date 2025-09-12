import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class WebApp {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/mydatabase";
    private static final String USER = "myuser";
    private static final String PASSWORD = "mypassword";

    public static Connection getDatabaseConnection() throws SQLException {
        return DriverManager.getConnection(DB_URL, USER, PASSWORD);
    }

    public static String getServerName() {
        return "localhost";
    }

    public static String getDatabaseName() {
        return "mydatabase";
    }

    public static String getDatabaseUser() {
        return "myuser";
    }

    public static String getDatabasePassword() {
        return "mypassword";
    }

    public static void main(String[] args) {
        try (Connection connection = getDatabaseConnection()) {
            System.out.println("Connected to database: " + getDatabaseName());
            System.out.println("Server Name: " + getServerName());
            System.out.println("User: " + getDatabaseUser());
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}


Note: This code assumes you have a MySQL server running locally with the specified database, user, and password. Adjust the `DB_URL`, `USER`, and `PASSWORD` constants as needed for your setup. Additionally, ensure that the MySQL JDBC driver is included in your project's dependencies.