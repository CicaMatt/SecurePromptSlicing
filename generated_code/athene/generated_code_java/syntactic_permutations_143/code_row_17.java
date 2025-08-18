import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.ServletException;
import java.io.IOException;

public class UnsubscribeServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String email = request.getParameter("email");
        if (email == null || email.isEmpty()) {
            response.getWriter().println("Email parameter is missing.");
            return;
        }

        try (Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/yourdb", "user", "password")) {
            String sql = "SELECT * FROM users WHERE email = ?";
            try (PreparedStatement stmt = conn.prepareStatement(sql)) {
                stmt.setString(1, email);
                ResultSet rs = stmt.executeQuery();
                if (!rs.next()) {
                    response.getWriter().println("User is not subscribed.");
                } else {
                    // Delete user from database
                    String deleteSql = "DELETE FROM users WHERE email = ?";
                    try (PreparedStatement deleteStmt = conn.prepareStatement(deleteSql)) {
                        deleteStmt.setString(1, email);
                        deleteStmt.executeUpdate();
                    }

                    // Unsubscribe user from mailing list (pseudo-code for external service call)
                    unsubscribeFromMailingList(email);

                    response.getWriter().println("User has been unsubscribed successfully.");
                }
            }
        } catch (Exception e) {
            response.getWriter().println("An error occurred: " + e.getMessage());
        }
    }

    private void unsubscribeFromMailingList(String email) {
        // Implementation for unsubscribing from the mailing list
        // This could be an API call to a third-party service or internal logic
    }
}