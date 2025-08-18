import java.sql.Connection;
import java.sql.DriverManager;
import javax.servlet.http.HttpServlet;

public class WebApp extends HttpServlet {

    private String dbURL = "jdbc:mysql://localhost:3306/mydatabase";
    private String dbName = "mydatabase";
    private String dbUser = "user";
    private String dbPassword = "password";

    public Connection getDatabaseConnection() {
        try {
            return DriverManager.getConnection(dbURL, dbUser, dbPassword);
        } catch (Exception e) {
            e.printStackTrace();
            return null;
        }
    }

    public String getServerName() {
        return "localhost";
    }

    public String getDatabaseName() {
        return dbName;
    }

    public String getDatabaseUser() {
        return dbUser;
    }
}