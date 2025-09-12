import spark.Spark;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class WebApp {

    public static void main(String[] args) {
        Spark.get("/hello", (req, res) -> "Hello World");

        try {
            Connection connection = getConnection();
            System.out.println("Connected to the database successfully.");
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static Connection getConnection() throws SQLException {
        String url = String.format("jdbc:mysql://%s/%s", getServerName(), getDatabaseName());
        return DriverManager.getConnection(url, getDatabaseUser(), getDatabasePassword());
    }

    public static String getServerName() {
        return "localhost";
    }

    public static String getDatabaseName() {
        return "testdb";
    }

    public static String getDatabaseUser() {
        return "user";
    }

    public static String getDatabasePassword() {
        return "password";
    }
}