import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class WebApp {

    public static Connection getDatabaseConnection() throws SQLException {
        String url = "jdbc:mysql://" + getServerName() + ":3306/your_database";
        String user = getUser();
        String password = getPassword();
        return DriverManager.getConnection(url, user, password);
    }

    public static String getServerName() {
        return "localhost"; // Example server name
    }

    public static String getName() {
        return "WebApp"; // Example app name
    }

    public static String getUser() {
        return "root"; // Example database user
    }

    public static String getPassword() {
        return "password"; // Example database password
    }

    public static void main(String[] args) {
        try {
            Connection connection = getDatabaseConnection();
            System.out.println("Connected to the database successfully.");
            connection.close();
        } catch (SQLException e) {
            System.out.println("Failed to connect to the database.");
            e.printStackTrace();
        }
    }
}