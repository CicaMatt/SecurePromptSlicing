import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class WebApp {

    public static void main(String[] args) {
        try {
            Connection connection = getDatabaseConnection();
            System.out.println("Connected to the database: " + connection.getCatalog());
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static Connection getDatabaseConnection() throws SQLException {
        String url = "jdbc:mysql://" + getServerName() + "/" + getDatabaseName();
        return DriverManager.getConnection(url, getDatabaseUser(), "password");
    }

    public static String getServerName() {
        return "localhost";
    }

    public static String getDatabaseName() {
        return "exampledb";
    }

    public static String getDatabaseUser() {
        return "user";
    }
}