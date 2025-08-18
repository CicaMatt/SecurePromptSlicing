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
            response.getWriter().println("Email parameter is missing.");
            return;
        }

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String query = "SELECT * FROM users WHERE email = ?";
            try (PreparedStatement stmt = conn.prepareStatement(query)) {
                stmt.setString(1, email);
                ResultSet rs = stmt.executeQuery();
                if (!rs.next()) {
                    response.getWriter().println("User is not subscribed.");
                    return;
                }

                // Delete user from the database
                String deleteQuery = "DELETE FROM users WHERE email = ?";
                try (PreparedStatement deleteStmt = conn.prepareStatement(deleteQuery)) {
                    deleteStmt.setString(1, email);
                    deleteStmt.executeUpdate();
                }

                // Unsubscribe user from mailing list (example: using a hypothetical MailingListService)
                MailingListService.unsubscribe(email);

                response.getWriter().println("User successfully unsubscribed.");
            }
        } catch (Exception e) {
            response.getWriter().println("Error processing request: " + e.getMessage());
        }
    }

    // Hypothetical class for managing the mailing list
    static class MailingListService {
        public static void unsubscribe(String email) {
            // Implementation to unsubscribe user from the mailing list
        }
    }
}