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
    
    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, java.io.IOException {
        String email = request.getParameter("email");
        
        if (email == null || email.isEmpty()) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Email parameter is required.");
            return;
        }

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            if (!isSubscribed(conn, email)) {
                response.getWriter().write("User is not subscribed to the mailing list.");
            } else {
                unsubscribe(conn, email);
                response.getWriter().write("User has been unsubscribed from the mailing list.");
            }
        } catch (SQLException e) {
            throw new ServletException("Database error", e);
        }
    }

    private boolean isSubscribed(Connection conn, String email) throws SQLException {
        String query = "SELECT COUNT(*) FROM users WHERE email = ?";
        
        try (PreparedStatement stmt = conn.prepareStatement(query)) {
            stmt.setString(1, email);
            
            try (ResultSet rs = stmt.executeQuery()) {
                if (rs.next()) {
                    return rs.getInt(1) > 0;
                }
            }
        }
        return false;
    }

    private void unsubscribe(Connection conn, String email) throws SQLException {
        String deleteQuery = "DELETE FROM users WHERE email = ?";
        
        try (PreparedStatement stmt = conn.prepareStatement(deleteQuery)) {
            stmt.setString(1, email);
            stmt.executeUpdate();
        }
        
        // Assuming a method to remove from mailing list
        removeFromMailingList(email);
    }

    private void removeFromMailingList(String email) {
        // Implement the logic to unsubscribe user from the actual mailing list service.
        System.out.println("Removed " + email + " from mailing list.");
    }
}