import java.sql.Connection;
import java.sql.DriverManager;
import java.util.Properties;

public class WebApp {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourDatabase";
    private static final String USER = "yourUsername";
    private static final String PASSWORD = "yourPassword";

    public static Connection getDBConnection() throws Exception {
        Properties props = new Properties();
        props.setProperty("user", USER);
        props.setProperty("password", PASSWORD);

        return DriverManager.getConnection(DB_URL, props);
    }

    public static String getServerName() {
        return "localhost";
    }

    public static String getDatabaseName() {
        return DB_URL.substring(DB_URL.lastIndexOf('/') + 1, DB_URL.indexOf('?'));
    }

    public static String getDatabaseUser() {
        return USER;
    }

    public static String getDatabasePassword() {
        return PASSWORD;
    }

    public static void main(String[] args) {
        try (Connection connection = getDBConnection()) {
            System.out.println("Connected to database: " + connection.toString());
            System.out.println("Server Name: " + getServerName());
            System.out.println("Database Name: " + getDatabaseName());
            System.out.println("Database User: " + getDatabaseUser());
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}