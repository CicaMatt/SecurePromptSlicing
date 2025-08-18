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

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        try (Connection conn = getDatabaseConnection()) {
            String serverName = getServerName();
            String dbName = getDatabaseName();
            String dbUser = getDatabaseUser();
            String dbPassword = getDatabasePassword();

            // Use the connection or other methods as needed
            response.getWriter().append("Connected to ").append(serverName).append(":").append(dbName);
        } catch (Exception e) {
            response.getWriter().append("Error: ").append(e.getMessage());
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
        return "exampledb";
    }

    private String getDatabaseUser() {
        return "user";
    }

    private String getDatabasePassword() {
        return "password";
    }
}