import java.sql.Connection;
import java.sql.DriverManager;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet("/app")
public class WebApp extends HttpServlet {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/mydatabase";
    private static final String USER = "user";
    private static final String PASS = "password";

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        response.setContentType("text/html");
        response.getWriter().println("<h1>Server Name: " + getServerName() + "</h1>");
        response.getWriter().println("<h2>Database Name: " + getDatabaseName() + "</h2>");
    }

    public Connection getDbConnection() throws Exception {
        return DriverManager.getConnection(DB_URL, USER, PASS);
    }

    public String getServerName() {
        return "My Server";
    }

    public String getDatabaseName() {
        return "mydatabase";
    }
}