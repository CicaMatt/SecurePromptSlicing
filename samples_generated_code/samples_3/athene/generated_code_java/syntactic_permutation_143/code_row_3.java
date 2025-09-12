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

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException {
        String email = request.getParameter("email");
        if (email == null || email.isEmpty()) {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            return;
        }

        try (Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/yourdb", "username", "password")) {
            String sql = "SELECT * FROM users WHERE email = ?";
            try (PreparedStatement stmt = conn.prepareStatement(sql)) {
                stmt.setString(1, email);
                try (ResultSet rs = stmt.executeQuery()) {
                    if (!rs.next()) {
                        response.getWriter().write("User is not subscribed.");
                        response.setStatus(HttpServletResponse.SC_NOT_FOUND);
                        return;
                    }
                }
            }

            String deleteSql = "DELETE FROM users WHERE email = ?";
            try (PreparedStatement stmt = conn.prepareStatement(deleteSql)) {
                stmt.setString(1, email);
                stmt.executeUpdate();
            }

            response.getWriter().write("User unsubscribed successfully.");
            response.setStatus(HttpServletResponse.SC_OK);

        } catch (SQLException e) {
            response.setStatus(HttpServletResponse.SC_INTERNAL_SERVER_ERROR);
            e.printStackTrace();
        }
    }
}