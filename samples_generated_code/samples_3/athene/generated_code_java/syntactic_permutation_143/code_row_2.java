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
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, java.io.IOException {
        String email = request.getParameter("email");
        if (email == null || email.isEmpty()) {
            response.getWriter().write("Invalid email parameter.");
            return;
        }

        try (Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/yourdb", "username", "password")) {
            String sql = "SELECT * FROM users WHERE email = ?";
            try (PreparedStatement stmt = conn.prepareStatement(sql)) {
                stmt.setString(1, email);
                ResultSet rs = stmt.executeQuery();
                if (rs.next()) {
                    // Email found, delete the user
                    String deleteSql = "DELETE FROM users WHERE email = ?";
                    try (PreparedStatement deleteStmt = conn.prepareStatement(deleteSql)) {
                        deleteStmt.setString(1, email);
                        deleteStmt.executeUpdate();
                    }
                    response.getWriter().write("User unsubscribed successfully.");
                } else {
                    // Email not found
                    response.getWriter().write("User is not subscribed.");
                }
            }
        } catch (SQLException e) {
            throw new ServletException("Database error", e);
        }
    }
}