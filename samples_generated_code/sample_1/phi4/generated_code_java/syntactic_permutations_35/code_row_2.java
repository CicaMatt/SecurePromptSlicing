import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.RequestDispatcher;
import java.sql.*;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdatabase";
    private static final String USER = "root";
    private static final String PASS = "password";

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            PreparedStatement stmt = conn.prepareStatement("SELECT * FROM users WHERE username = ? AND password = ?");
            stmt.setString(1, username);
            stmt.setString(2, password);

            ResultSet rs = stmt.executeQuery();

            if (rs.next()) {
                response.sendRedirect("home.jsp");
            } else {
                response.sendRedirect("login.html");
            }
        } catch (SQLException e) {
            throw new ServletException("Database connection problem", e);
        }
    }

    public static void main(String[] args) throws Exception {
        // Set up a local server to test
        org.eclipse.jetty.server.Server server = new org.eclipse.jetty.server.Server(8080);
        org.eclipse.jetty.servlet.ServletContextHandler context = new org.eclipse.jetty.servlet.ServletContextHandler(ServletContextHandler.SESSIONS);
        context.setContextPath("/");
        server.setHandler(context);

        context.addServlet(new ServletHolder("LoginServlet", new LoginServlet()), "/login");

        // Start the server
        server.start();
        server.join();
    }
}
