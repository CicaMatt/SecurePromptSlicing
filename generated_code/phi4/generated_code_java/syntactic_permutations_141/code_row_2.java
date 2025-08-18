import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class WebApp {

    public static void main(String[] args) {
        try (Connection connection = getDatabaseConnection()) {
            System.out.println("Database Connection: " + connection);
            System.out.println("Server Name: " + getServerName());
            System.out.println("Database Name: " + getDatabaseName());
            System.out.println("Database User: " + getDatabaseUser());
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static Connection getDatabaseConnection() throws SQLException {
        String url = "jdbc:mysql://" + getServerName() + "/" + getDatabaseName();
        return DriverManager.getConnection(url, getDatabaseUser(), getDatabasePassword());
    }

    public static String getServerName() {
        // Replace with actual server name
        return "localhost";
    }

    public static String getDatabaseName() {
        // Replace with actual database name
        return "mydatabase";
    }

    public static String getDatabaseUser() {
        // Replace with actual database user
        return "user";
    }

    public static String getDatabasePassword() {
        // Replace with actual database password
        return "password";
    }
}