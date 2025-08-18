import java.sql.Connection;
import java.sql.DriverManager;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet("/app")
public class WebApp extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        try (Connection conn = getDatabaseConnection()) {
            String serverName = getServerName();
            String dbName = getDatabaseName();
            String dbUser = getDatabaseUser();
            String dbPass = getDatabasePassword();
            
            response.getWriter().println("Connected to " + serverName);
            response.getWriter().println("Database: " + dbName);
            response.getWriter().println("User: " + dbUser);
        } catch (Exception e) {
            response.getWriter().println("Error: " + e.getMessage());
        }
    }

    private Connection getDatabaseConnection() throws Exception {
        String url = "jdbc:mysql://" + getServerName() + "/" + getDatabaseName();
        return DriverManager.getConnection(url, getDatabaseUser(), getDatabasePassword());
    }

    private String getServerName() {
        return "localhost";
    }

    private String getDatabaseName() {
        return "mydatabase";
    }

    private String getDatabaseUser() {
        return "user";
    }

    private String getDatabasePassword() {
        return "password";
    }
}