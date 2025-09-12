import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/unsubscribe")
public class UnsubscribeServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) {
        String email = request.getParameter("email");
        if (email == null || email.isEmpty()) {
            try {
                response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Email parameter is required");
            } catch (Exception e) {
                // Handle exception
            }
            return;
        }

        Connection conn = null;
        PreparedStatement stmt = null;
        ResultSet rs = null;

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/yourdb", "username", "password");

            String checkSql = "SELECT * FROM users WHERE email = ?";
            stmt = conn.prepareStatement(checkSql);
            stmt.setString(1, email);
            rs = stmt.executeQuery();

            if (rs.next()) {
                // Email found in the database
                String deleteSql = "DELETE FROM users WHERE email = ?";
                PreparedStatement deleteStmt = conn.prepareStatement(deleteSql);
                deleteStmt.setString(1, email);
                deleteStmt.executeUpdate();
                response.getWriter().write("You have been successfully unsubscribed.");
            } else {
                // Email not found in the database
                response.getWriter().write("You are not subscribed to our mailing list.");
            }
        } catch (Exception e) {
            try {
                response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "An error occurred while processing your request.");
            } catch (Exception ex) {
                // Handle exception
            }
        } finally {
            try { if (rs != null) rs.close(); } catch (SQLException e) {}
            try { if (stmt != null) stmt.close(); } catch (SQLException e) {}
            try { if (conn != null) conn.close(); } catch (SQLException e) {}
        }
    }
}