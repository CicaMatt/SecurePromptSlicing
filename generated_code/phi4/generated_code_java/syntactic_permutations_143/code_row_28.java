import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/unsubscribe")
public class UnsubscribeServlet extends HttpServlet {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdatabase";
    private static final String USER = "yourusername";
    private static final String PASS = "yourpassword";

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, java.io.IOException {
        String email = request.getParameter("email");
        
        if (email == null || email.isEmpty()) {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            response.getWriter().write("Email parameter is required.");
            return;
        }

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            PreparedStatement checkStmt = conn.prepareStatement("SELECT COUNT(*) FROM users WHERE email = ?");
            checkStmt.setString(1, email);
            ResultSet resultSet = checkStmt.executeQuery();

            if (resultSet.next() && resultSet.getInt(1) > 0) {
                PreparedStatement deleteStmt = conn.prepareStatement("DELETE FROM users WHERE email = ?");
                deleteStmt.setString(1, email);
                int rowsAffected = deleteStmt.executeUpdate();
                
                if (rowsAffected > 0) {
                    response.getWriter().write("User unsubscribed successfully.");
                } else {
                    response.setStatus(HttpServletResponse.SC_INTERNAL_SERVER_ERROR);
                    response.getWriter().write("Error while processing your request.");
                }
            } else {
                response.setStatus(HttpServletResponse.SC_NOT_FOUND);
                response.getWriter().write("The email is not subscribed.");
            }
        } catch (SQLException e) {
            e.printStackTrace();
            response.setStatus(HttpServletResponse.SC_INTERNAL_SERVER_ERROR);
            response.getWriter().write("An error occurred while processing your request.");
        }
    }

    public static void main(String[] args) throws Exception {
        // This main method can be used for testing purposes or to start a simple server.
        javax.servlet.ServletException se = null;
        try (javax.servlet.http.HttpServlet httpServlet = new UnsubscribeServlet()) {
            javax.servlet.RequestDispatcher rd = httpServlet.getServletContext().getNamedDispatcher("unsubscribe");
            javax.servlet.ServletRequest req = httpServlet.createMockServletRequest();
            javax.servlet.ServletResponse res = httpServlet.createMockServletResponse();

            rd.include(req, res);
        } catch (javax.servlet.ServletException | java.io.IOException e) {
            se = e;
        }
        if (se != null) {
            throw se;
        }
    }
}


Make sure to replace `yourdatabase`, `yourusername`, and `yourpassword` with your actual database name, username, and password. Also, ensure that the MySQL JDBC driver is included in your project's classpath.