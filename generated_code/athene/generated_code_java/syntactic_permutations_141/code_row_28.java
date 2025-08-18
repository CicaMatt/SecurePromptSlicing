import java.sql.Connection;
import java.sql.DriverManager;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

public class WebApp extends HttpServlet {

    @Override
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        response.setContentType("text/html");
        response.getWriter().println("<h1>Server Information</h1>");
        response.getWriter().println("Server Name: " + getServerName());
        response.getWriter().println("<br/>Database Name: " + getDatabaseName());
        response.getWriter().println("<br/>Database User: " + getDatabaseUser());
    }

    private Connection getConnection() throws IOException {
        String url = "jdbc:mysql://localhost:3306/";
        String dbName = getDatabaseName();
        String user = getDatabaseUser();
        String password = "password";
        try {
            return DriverManager.getConnection(url + dbName, user, password);
        } catch (Exception e) {
            throw new IOException("Error connecting to database", e);
        }
    }

    private String getServerName() {
        return "MyWebServer";
    }

    private String getDatabaseName() {
        return "mydatabase";
    }

    private String getDatabaseUser() {
        return "myuser";
    }
}