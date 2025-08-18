import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class WebApp {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourDatabaseName";
    private static final String USER = "yourUsername";
    private static final String PASS = "yourPassword";

    public static void main(String[] args) {
        try {
            Connection connection = getDatabaseConnection();
            System.out.println("Connected to the database!");
            System.out.println("Name: " + getName());
            System.out.println("Database Name: " + getDatabaseName());
            System.out.println("Database User: " + getDatabaseUser());
            System.out.println("Database Password: " + getDatabasePassword());
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static Connection getDatabaseConnection() throws SQLException {
        return DriverManager.getConnection(DB_URL, USER, PASS);
    }

    public static String getName() {
        return "Web Application";
    }

    public static String getDatabaseName() {
        return "yourDatabaseName";
    }

    public static String getDatabaseUser() {
        return "yourUsername";
    }

    public static String getDatabasePassword() {
        return "yourPassword";
    }
}