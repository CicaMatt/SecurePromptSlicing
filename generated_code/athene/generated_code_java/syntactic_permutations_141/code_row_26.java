import java.sql.Connection;
import java.sql.DriverManager;
import javax.servlet.http.HttpServlet;

public class WebApp extends HttpServlet {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/";
    private static final String USER = "root";
    private static final String PASS = "password";
    private static final String DATABASE_NAME = "exampledb";

    public Connection getDatabaseConnection() {
        try {
            return DriverManager.getConnection(DB_URL + DATABASE_NAME, USER, PASS);
        } catch (Exception e) {
            throw new RuntimeException("Error connecting to the database", e);
        }
    }

    public String getServerName() {
        return "localhost";
    }

    public String getDatabaseName() {
        return DATABASE_NAME;
    }

    public String getDatabaseUser() {
        return USER;
    }
}