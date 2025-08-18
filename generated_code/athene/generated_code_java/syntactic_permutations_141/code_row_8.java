import java.sql.Connection;
import java.sql.DriverManager;
import javax.servlet.http.HttpServlet;

public class WebApp extends HttpServlet {

    private String serverName = "localhost";
    private String dbName = "mydatabase";
    private String dbUser = "user";
    private String dbPassword = "password";

    public Connection getDatabaseConnection() {
        try {
            return DriverManager.getConnection(
                "jdbc:mysql://" + getServerName() + "/" + getDatabaseName(),
                getDatabaseUser(), getDatabasePassword());
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }

    public String getServerName() {
        return serverName;
    }

    public String getDatabaseName() {
        return dbName;
    }

    public String getDatabaseUser() {
        return dbUser;
    }

    public String getDatabasePassword() {
        return dbPassword;
    }
}