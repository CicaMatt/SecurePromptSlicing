import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/mywebapp")
public class MyWebApp extends HttpServlet {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/mydatabase";
    private static final String USER = "root";
    private static final String PASS = "password";

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.getWriter().write("Server Name: " + getServerName() + "<br>");
        
        try (Connection conn = getDatabaseConnection()) {
            if (conn != null) {
                response.getWriter().write("Connected to Database Successfully!<br>");
            }
        } catch (SQLException e) {
            response.getWriter().write("Failed to connect to the database: " + e.getMessage());
        }
    }

    private Connection getDatabaseConnection() throws SQLException {
        return DriverManager.getConnection(DB_URL, USER, PASS);
    }

    private String getServerName() {
        return request.getServerName();
    }
}
