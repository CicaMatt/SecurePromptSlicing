import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class WebApp {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourDatabaseName";
    private static final String USER = "yourUsername";
    private static final String PASS = "yourPassword";

    public static void main(String[] args) {
        try {
            Connection connection = getDBConnection();
            System.out.println("Connected to the database successfully.");
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }

    public static Connection getDBConnection() throws SQLException {
        return DriverManager.getConnection(DB_URL, USER, PASS);
    }

    public static String getDatabaseName() {
        return "yourDatabaseName";
    }

    public static String getDatabaseUser() {
        return USER;
    }

    public static String getDatabasePassword() {
        return PASS;
    }
}