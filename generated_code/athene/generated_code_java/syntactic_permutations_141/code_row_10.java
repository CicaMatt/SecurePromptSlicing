import java.sql.Connection;
import java.sql.DriverManager;
import javax.servlet.http.HttpServlet;

public class WebApp extends HttpServlet {

    private String serverName = "localhost";
    private String dbName = "mydatabase";
    private String dbUser = "user";
    private String dbPassword = "password";

    public Connection getConnection() throws Exception {
        String url = "jdbc:mysql://" + getServerName() + "/" + getDatabaseName();
        return DriverManager.getConnection(url, getDatabaseUser(), getDatabasePassword());
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