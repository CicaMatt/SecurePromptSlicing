import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
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

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String email = request.getParameter("email");
        if (email == null || email.isEmpty()) {
            response.getWriter().println("Email parameter is missing");
            return;
        }

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String query = "SELECT * FROM users WHERE email = ?";
            try (PreparedStatement stmt = conn.prepareStatement(query)) {
                stmt.setString(1, email);
                ResultSet rs = stmt.executeQuery();
                if (!rs.next()) {
                    response.getWriter().println("User is not subscribed");
                } else {
                    deleteFromDatabase(conn, email);
                    unsubscribeFromMailingList(email);
                    response.getWriter().println("Successfully unsubscribed");
                }
            }
        } catch (Exception e) {
            response.getWriter().println("An error occurred: " + e.getMessage());
        }
    }

    private void deleteFromDatabase(Connection conn, String email) throws Exception {
        String query = "DELETE FROM users WHERE email = ?";
        try (PreparedStatement stmt = conn.prepareStatement(query)) {
            stmt.setString(1, email);
            stmt.executeUpdate();
        }
    }

    private void unsubscribeFromMailingList(String email) {
        // Implement the logic to unsubscribe from the mailing list
        // This could be an API call or a method in your mailing service provider
    }
}