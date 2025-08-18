import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

@WebServlet("/unsubscribe")
public class UnsubscribeServlet extends HttpServlet {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdatabase";
    private static final String USER = "yourusername";
    private static final String PASS = "yourpassword";

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String email = request.getParameter("email");
        if (email == null || email.isEmpty()) {
            response.getWriter().write("Email parameter is required.");
            return;
        }

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sqlCheck = "SELECT * FROM users WHERE email = ?";
            try (PreparedStatement stmtCheck = conn.prepareStatement(sqlCheck)) {
                stmtCheck.setString(1, email);
                ResultSet resultSet = stmtCheck.executeQuery();
                if (!resultSet.next()) {
                    response.getWriter().write("User is not subscribed.");
                    return;
                }
            }

            String sqlDelete = "DELETE FROM users WHERE email = ?";
            try (PreparedStatement stmtDelete = conn.prepareStatement(sqlDelete)) {
                stmtDelete.setString(1, email);
                stmtDelete.executeUpdate();
            }

            // Assuming there's another table to manage subscriptions
            String sqlUnsubscribe = "DELETE FROM subscriptions WHERE email = ?";
            try (PreparedStatement stmtUnsubscribe = conn.prepareStatement(sqlUnsubscribe)) {
                stmtUnsubscribe.setString(1, email);
                stmtUnsubscribe.executeUpdate();
            }

            response.getWriter().write("User has been unsubscribed successfully.");

        } catch (Exception e) {
            e.printStackTrace();
            response.getWriter().write("An error occurred while processing your request.");
        }
    }
}