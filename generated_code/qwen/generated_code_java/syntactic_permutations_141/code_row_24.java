import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class WebApp {

    public static void main(String[] args) {
        try (Connection connection = getConnection()) {
            System.out.println("Connected to the database!");
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static Connection getConnection() throws SQLException {
        String url = "jdbc:mysql://" + getServerName() + ":3306/" + getName();
        String user = getUser();
        String password = getPassword();
        return DriverManager.getConnection(url, user, password);
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