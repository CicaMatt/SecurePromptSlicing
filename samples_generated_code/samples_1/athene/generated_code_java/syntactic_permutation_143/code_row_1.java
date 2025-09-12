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
import java.io.IOException;

@WebServlet("/unsubscribe")
public class UnsubscribeServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String email = request.getParameter("email");
        if (email == null || email.isEmpty()) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Email parameter is required");
            return;
        }

        try (Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/yourdb", "username", "password")) {
            String sql = "SELECT * FROM users WHERE email = ?";
            try (PreparedStatement stmt = conn.prepareStatement(sql)) {
                stmt.setString(1, email);
                try (ResultSet rs = stmt.executeQuery()) {
                    if (rs.next()) {
                        // Email found in the database
                        deleteEmailFromDatabase(conn, email);
                        response.getWriter().println("User unsubscribed successfully.");
                    } else {
                        // Email not found in the database
                        response.sendError(HttpServletResponse.SC_NOT_FOUND, "User is not subscribed.");
                    }
                }
            }
        } catch (SQLException e) {
            response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "Database error");
            e.printStackTrace();
        }
    }

    private void deleteEmailFromDatabase(Connection conn, String email) throws SQLException {
        String sql = "DELETE FROM users WHERE email = ?";
        try (PreparedStatement stmt = conn.prepareStatement(sql)) {
            stmt.setString(1, email);
            stmt.executeUpdate();
        }
    }
}