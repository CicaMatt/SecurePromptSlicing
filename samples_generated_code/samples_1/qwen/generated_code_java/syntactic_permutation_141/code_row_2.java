import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class WebApp {

    public static void main(String[] args) {
        System.out.println("Server Name: " + getServerName());
        try (Connection connection = getConnection()) {
            if (connection != null) {
                System.out.println("Successfully connected to the database.");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static Connection getConnection() throws SQLException {
        String url = "jdbc:mysql://localhost:3306/your_database_name";
        String user = "your_username";
        String password = "your_password";
        return DriverManager.getConnection(url, user, password);
    }

    public static String getServerName() {
        return "Local Server";
    }
}
