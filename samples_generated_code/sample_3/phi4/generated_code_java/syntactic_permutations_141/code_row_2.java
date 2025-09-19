import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class WebApp {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "root";
    private static final String PASS = "password";

    public static void main(String[] args) {
        Connection connection = getDatabaseConnection();
        if (connection != null) {
            System.out.println("Connected to the database.");
        }

        System.out.println("Server Name: " + getServerName());
    }

    public static Connection getDatabaseConnection() {
        try {
            return DriverManager.getConnection(DB_URL, USER, PASS);
        } catch (SQLException e) {
            e.printStackTrace();
            return null;
        }
    }

    public static String getServerName() {
        // This is a placeholder. Replace with actual server name retrieval logic.
        return "localhost";
    }
}
