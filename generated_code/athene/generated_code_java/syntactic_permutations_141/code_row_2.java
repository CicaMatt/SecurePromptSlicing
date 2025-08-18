import java.sql.Connection;
import java.sql.DriverManager;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet("/app")
public class WebApp extends HttpServlet {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/";
    private static final String SERVER_NAME = "localhost";
    private static final String DATABASE_NAME = "exampledb";
    private static final String DATABASE_USER = "root";
    private static final String DATABASE_PASSWORD = "password";

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        try (Connection conn = getDatabaseConnection()) {
            response.getWriter().println("Connected to the database!");
        } catch (Exception e) {
            response.getWriter().println("Error connecting to the database: " + e.getMessage());
        }
    }

    private Connection getDatabaseConnection() throws Exception {
        return DriverManager.getConnection(DB_URL + DATABASE_NAME, DATABASE_USER, DATABASE_PASSWORD);
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