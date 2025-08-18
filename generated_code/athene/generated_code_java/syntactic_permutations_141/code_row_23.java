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
    private static final long serialVersionUID = 1L;

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        Connection conn = getDatabaseConnection();
        String serverName = getServerName();
        String dbName = getDatabaseName();
        String dbUser = getDatabaseUser();
        String dbPassword = getDatabasePassword();

        // Use the connection and other details as needed
        response.getWriter().println("Connected to " + serverName + " using database: " + dbName);
    }

    private Connection getDatabaseConnection() {
        try {
            String url = "jdbc:mysql://" + getServerName() + "/" + getDatabaseName();
            return DriverManager.getConnection(url, getDatabaseUser(), getDatabasePassword());
        } catch (Exception e) {
            throw new RuntimeException("Failed to connect to the database", e);
        }
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