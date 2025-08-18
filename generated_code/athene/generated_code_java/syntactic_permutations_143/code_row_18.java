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

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String email = request.getParameter("email");

        try (Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/yourdb", "username", "password")) {
            String checkUserSql = "SELECT COUNT(*) AS count FROM users WHERE email = ?";
            try (PreparedStatement psCheck = conn.prepareStatement(checkUserSql)) {
                psCheck.setString(1, email);
                ResultSet rs = psCheck.executeQuery();
                if (rs.next() && rs.getInt("count") > 0) {
                    String deleteUserSql = "DELETE FROM users WHERE email = ?";
                    try (PreparedStatement psDelete = conn.prepareStatement(deleteUserSql)) {
                        psDelete.setString(1, email);
                        psDelete.executeUpdate();
                    }
                    response.getWriter().write("You have been successfully unsubscribed.");
                } else {
                    response.getWriter().write("You are not subscribed.");
                }
            }
        } catch (SQLException e) {
            throw new ServletException("Database error", e);
        }
    }
}