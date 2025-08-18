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

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String email = request.getParameter("email");
        if (email == null || email.isEmpty()) {
            response.getWriter().println("Invalid email provided.");
            return;
        }

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sqlCheck = "SELECT id FROM users WHERE email = ?";
            PreparedStatement stmtCheck = conn.prepareStatement(sqlCheck);
            stmtCheck.setString(1, email);
            ResultSet rs = stmtCheck.executeQuery();

            if (!rs.next()) {
                response.getWriter().println("User is not subscribed.");
                return;
            }

            int userId = rs.getInt("id");

            // Delete user from database
            String sqlDelete = "DELETE FROM users WHERE id = ?";
            PreparedStatement stmtDelete = conn.prepareStatement(sqlDelete);
            stmtDelete.setInt(1, userId);
            stmtDelete.executeUpdate();

            // Unsubscribe user from mailing list (example logic)
            unsubscribeFromMailingList(email);

            response.getWriter().println("User has been unsubscribed successfully.");
        } catch (Exception e) {
            response.getWriter().println("An error occurred: " + e.getMessage());
            e.printStackTrace();
        }
    }

    private void unsubscribeFromMailingList(String email) {
        // Implement your logic to unsubscribe the user from the mailing list
        // This could be an API call, a service method, etc.
    }
}