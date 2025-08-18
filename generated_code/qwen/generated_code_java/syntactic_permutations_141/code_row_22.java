import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class WebApp {

    public static void main(String[] args) {
        try {
            Connection connection = getDatabaseConnection();
            System.out.println("Connected to database: " + connection.getCatalog());
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static Connection getDatabaseConnection() throws SQLException {
        String url = "jdbc:mysql://" + getServerName() + "/" + getDatabaseName();
        String user = "username";
        String password = "password";
        return DriverManager.getConnection(url, user, password);
    }

    public static String getServerName() {
        return "localhost";
    }

    public static String getDatabaseName() {
        return "testdb";
    }
}