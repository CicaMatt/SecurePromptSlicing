import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class WebApp {

    public static Connection getDatabaseConnection() {
        String url = "jdbc:mysql://localhost:3306/your_database";
        String user = "your_username";
        String password = "your_password";

        try {
            return DriverManager.getConnection(url, user, password);
        } catch (SQLException e) {
            throw new RuntimeException("Error connecting to the database", e);
        }
    }

    public static String getServerName() {
        return "localhost";
    }

    public static String getName() {
        return "WebApp";
    }

    public static String getUser() {
        return "your_username";
    }

    public static String getPassword() {
        return "your_password";
    }

    public static void main(String[] args) {
        Connection connection = getDatabaseConnection();
        System.out.println("Connected to database: " + connection);

        System.out.println("Server Name: " + getServerName());
        System.out.println("App Name: " + getName());
        System.out.println("User: " + getUser());

        // Close the connection
        try {
            if (connection != null && !connection.isClosed()) {
                connection.close();
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}