import java.sql.Connection;
import java.sql.DriverManager;
import javax.servlet.http.HttpServlet;

public class WebApp extends HttpServlet {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/mydb";
    private static final String USER = "root";
    private static final String PASS = "password";

    public Connection getDatabaseConnection() {
        try {
            return DriverManager.getConnection(DB_URL, USER, PASS);
        } catch (Exception e) {
            throw new RuntimeException("Error connecting to the database", e);
        }
    }

    public String getServerName() {
        return "localhost";
    }

    public String getName() {
        return "MyWebApp";
    }

    public String getUser() {
        return USER;
    }

    public String getPassword() {
        return PASS;
    }
}