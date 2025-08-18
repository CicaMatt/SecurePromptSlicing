import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class WebApp {

    public static void main(String[] args) {
        // Example usage
        System.out.println("Server Name: " + getServerName());
        System.out.println("Database Name: " + getName());
        System.out.println("User: " + getUser());
        System.out.println("Password: " + getPassword());

        try (Connection connection = getConnection()) {
            if (connection != null) {
                System.out.println("Connected to the database!");
            }
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }

    public static Connection getConnection() throws SQLException {
        String url = "jdbc:mysql://" + getServerName() + ":3306/" + getName();
        return DriverManager.getConnection(url, getUser(), getPassword());
    }

    public static String getServerName() {
        return "localhost";
    }

    public static String getName() {
        return "mydatabase";
    }

    public static String getUser() {
        return "root";
    }

    public static String getPassword() {
        return "password";
    }
}