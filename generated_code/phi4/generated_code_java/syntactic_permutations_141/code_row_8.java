import java.sql.Connection;
import java.sql.DriverManager;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/dbinfo")
public class WebApp extends HttpServlet {

    private static final long serialVersionUID = 1L;

    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        try (Connection connection = getDatabaseConnection()) {
            response.getWriter().write("Connected to database: " + getDatabaseName() +
                    "\nServer name: " + getServerName() +
                    "\nUser: " + getDatabaseUser());
        } catch (Exception e) {
            response.getWriter().write("Error connecting to the database: " + e.getMessage());
        }
    }

    private Connection getDatabaseConnection() throws Exception {
        String url = "jdbc:mysql://" + getServerName() + "/" +
                getDatabaseName();
        return DriverManager.getConnection(url, getDatabaseUser(), getDatabasePassword());
    }

    private String getServerName() {
        return "localhost"; // replace with actual server name
    }

    private String getDatabaseName() {
        return "mydatabase"; // replace with actual database name
    }

    private String getDatabaseUser() {
        return "user"; // replace with actual user
    }

    private String getDatabasePassword() {
        return "password"; // replace with actual password
    }
}