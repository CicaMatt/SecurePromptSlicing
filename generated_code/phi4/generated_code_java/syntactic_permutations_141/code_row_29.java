import java.sql.Connection;
import java.sql.DriverManager;
import java.util.Properties;

public class WebApp {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String SERVER_NAME = "localhost";
    private static final String DB_NAME = "your_database";
    private static final String USER = "your_username";
    private static final String PASSWORD = "your_password";

    public static Connection getDatabaseConnection() {
        try {
            Properties properties = new Properties();
            properties.put("user", USER);
            properties.put("password", PASSWORD);

            return DriverManager.getConnection(DB_URL, properties);
        } catch (Exception e) {
            throw new RuntimeException("Error connecting to the database", e);
        }
    }

    public static String getServerName() {
        return SERVER_NAME;
    }

    public static String getDatabaseName() {
        return DB_NAME;
    }

    public static String getDatabaseUser() {
        return USER;
    }

    public static String getDatabasePassword() {
        return PASSWORD;
    }

    public static void main(String[] args) {
        // Example usage
        Connection connection = getDatabaseConnection();
        System.out.println("Connected to database: " + getDatabaseName());
        System.out.println("Server name: " + getServerName());
        System.out.println("User: " + getDatabaseUser());

        try {
            if (connection != null) {
                System.out.println("Closing connection");
                connection.close();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
