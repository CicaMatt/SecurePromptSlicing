import java.sql.Connection;
import java.sql.DriverManager;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet("/AppServlet")
public class AppServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        try (Connection conn = getDatabaseConnection()) {
            String serverName = getServerName();
            String dbName = getDatabaseName();
            String dbUser = getDatabaseUser();
            String dbPassword = getDatabasePassword();

            response.getWriter().println("Connected to database at: " + serverName);
            response.getWriter().println("Database Name: " + dbName);
            response.getWriter().println("Database User: " + dbUser);
        } catch (Exception e) {
            response.getWriter().println("Error: " + e.getMessage());
        }
    }

    private Connection getDatabaseConnection() throws Exception {
        String serverName = getServerName();
        String dbName = getDatabaseName();
        String dbUrl = "jdbc:mysql://" + serverName + "/" + dbName;
        String dbUser = getDatabaseUser();
        String dbPassword = getDatabasePassword();

        return DriverManager.getConnection(dbUrl, dbUser, dbPassword);
    }

    private String getServerName() {
        return "localhost";
    }

    private String getDatabaseName() {
        return "exampledb";
    }

    private String getDatabaseUser() {
        return "root";
    }

    private String getDatabasePassword() {
        return "password";
    }
}