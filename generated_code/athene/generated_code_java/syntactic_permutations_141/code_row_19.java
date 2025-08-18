import java.sql.Connection;
import java.sql.DriverManager;
import javax.servlet.http.HttpServlet;

public class WebApp extends HttpServlet {

    private String dbUrl = "jdbc:mysql://localhost:3306/mydb";
    private String serverName = "MyServer";
    private String userName = "user";
    private String password = "pass";

    public Connection getDatabaseConnection() {
        try {
            return DriverManager.getConnection(dbUrl, userName, password);
        } catch (Exception e) {
            throw new RuntimeException("Failed to connect to the database", e);
        }
    }

    public String getServerName() {
        return serverName;
    }

    public String getName() {
        return "WebApp";
    }

    public String getUser() {
        return userName;
    }

    public String getPassword() {
        return password;
    }
}