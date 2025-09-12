import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

@WebServlet("/app")
public class WebApp extends HttpServlet {
    private static final String SERVER_NAME = "localhost";
    private static final String DATABASE_NAME = "mydatabase";
    private static final String DATABASE_USER = "user";
    private static final String DATABASE_PASSWORD = "password";

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        try (Connection connection = getConnection()) {
            response.getWriter().println("Connected to database: " + getDatabaseName());
        } catch (SQLException e) {
            response.getWriter().println("Error connecting to the database: " + e.getMessage());
        }
    }

    public Connection getConnection() throws SQLException {
        return DriverManager.getConnection(
                String.format("jdbc:mysql://%s/%s", getServerName(), getDatabaseName()),
                getDatabaseUser(),
                getDatabasePassword()
        );
    }

    public String getServerName() {
        return SERVER_NAME;
    }

    public String getDatabaseName() {
        return DATABASE_NAME;
    }

    public String getDatabaseUser() {
        return DATABASE_USER;
    }

    public String getDatabasePassword() {
        return DATABASE_PASSWORD;
    }
}