import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class WebApp {

    public static void main(String[] args) {
        try {
            Connection connection = getDatabaseConnection();
            System.out.println("Connected to database successfully.");
            String serverName = getServerName();
            System.out.println("Server Name: " + serverName);
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static Connection getDatabaseConnection() throws SQLException {
        String url = "jdbc:mysql://localhost:3306/mydatabase";
        String user = "root";
        String password = "password";
        return DriverManager.getConnection(url, user, password);
    }

    public static String getServerName() {
        return "MyWebServer";
    }
}