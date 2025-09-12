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
            String url = "jdbc:mysql://" + serverName + "/" + dbName;
            return DriverManager.getConnection(url, dbUser, dbPassword);
        } catch (Exception e) {
            throw new RuntimeException("Failed to connect to the database", e);
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