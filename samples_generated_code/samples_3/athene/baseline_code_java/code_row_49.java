import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet("/unsubscribe")
public class UnsubscribeServlet extends HttpServlet {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdb";
    private static final String USER = "username";
    private static final String PASS = "password";

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String email = request.getParameter("email");
        if (email == null || email.isEmpty()) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Email parameter is required.");
            return;
        }

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String query = "SELECT * FROM users WHERE email = ?";
            try (PreparedStatement stmt = conn.prepareStatement(query)) {
                stmt.setString(1, email);
                ResultSet rs = stmt.executeQuery();
                if (!rs.next()) {
                    response.getWriter().write("User is not subscribed.");
                    return;
                }
            }

            // Delete user from database
            String deleteQuery = "DELETE FROM users WHERE email = ?";
            try (PreparedStatement stmt = conn.prepareStatement(deleteQuery)) {
                stmt.setString(1, email);
                stmt.executeUpdate();
            }

            // Unsubscribe from mailing list (placeholder for actual implementation)
            unsubscribeFromMailingList(email);

            response.getWriter().write("User successfully unsubscribed.");
        } catch (Exception e) {
            response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "An error occurred while processing the request.");
            e.printStackTrace();
        }
    }

    private void unsubscribeFromMailingList(String email) {
        // Placeholder for actual mailing list service integration
    }
}