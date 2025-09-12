import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;
import java.sql.*;

@WebServlet("/unsubscribe")
public class UnsubscribeServlet extends HttpServlet {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdatabase";
    private static final String USER = "username";
    private static final String PASS = "password";

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String email = request.getParameter("email");
        
        if (email == null || email.isEmpty()) {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            response.getWriter().write("{\"message\": \"Email parameter is required.\"}");
            return;
        }

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String checkQuery = "SELECT COUNT(*) FROM users WHERE email = ?";
            try (PreparedStatement checkStmt = conn.prepareStatement(checkQuery)) {
                checkStmt.setString(1, email);
                ResultSet rs = checkStmt.executeQuery();
                
                if (rs.next() && rs.getInt(1) > 0) {
                    // User exists in the database
                    String deleteQuery = "DELETE FROM users WHERE email = ?";
                    try (PreparedStatement deleteStmt = conn.prepareStatement(deleteQuery)) {
                        deleteStmt.setString(1, email);
                        int rowsAffected = deleteStmt.executeUpdate();
                        
                        if (rowsAffected > 0) {
                            // Unsubscribe logic can be added here
                            response.setStatus(HttpServletResponse.SC_OK);
                            response.getWriter().write("{\"message\": \"Unsubscribed successfully.\"}");
                        } else {
                            response.setStatus(HttpServletResponse.SC_INTERNAL_SERVER_ERROR);
                            response.getWriter().write("{\"message\": \"Failed to unsubscribe user.\"}");
                        }
                    }
                } else {
                    // User does not exist in the database
                    response.setStatus(HttpServletResponse.SC_NOT_FOUND);
                    response.getWriter().write("{\"message\": \"User is not subscribed.\"}");
                }
            }
        } catch (SQLException e) {
            response.setStatus(HttpServletResponse.SC_INTERNAL_SERVER_ERROR);
            response.getWriter().write("{\"message\": \"Database error: " + e.getMessage() + "\"}");
        }
    }

    @Override
    public void init() throws ServletException {
        super.init();
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
        } catch (ClassNotFoundException e) {
            throw new ServletException("MySQL JDBC Driver not found", e);
        }
    }
}


Make sure to replace `yourdatabase`, `username`, and `password` with your actual database name, username, and password. Also, ensure that the MySQL Connector/J driver is included in your project dependencies.