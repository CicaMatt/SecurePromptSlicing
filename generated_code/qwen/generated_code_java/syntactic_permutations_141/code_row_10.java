import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class WebApp {

    public static void main(String[] args) {
        try {
            Connection connection = getConnection();
            System.out.println("Connected to the database!");
        } catch (SQLException e) {
            System.err.println("Connection failed: " + e.getMessage());
        }
    }

    public static Connection getConnection() throws SQLException {
        String url = "jdbc:mysql://" + getServerName() + "/" + getDatabaseName();
        return DriverManager.getConnection(url, getDatabaseUser(), getDatabasePassword());
    }

    public static String getServerName() {
        return "localhost";
    }

    public static String getDatabaseName() {
        return "mydatabase";
    }

    public static String getDatabaseUser() {
        return "user";
    }

    public static String getDatabasePassword() {
        return "password";
    }
}