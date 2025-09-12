import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;

@WebServlet("/unsubscribe")
public class UnsubscribeServlet extends HttpServlet {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/emaildb";
    private static final String USER = "root";
    private static final String PASS = "password";

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String email = request.getParameter("email");
        if (email == null || email.isEmpty()) {
            response.getWriter().println("Email parameter is missing.");
            return;
        }

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "SELECT * FROM users WHERE email = ?";
            try (PreparedStatement stmt = conn.prepareStatement(sql)) {
                stmt.setString(1, email);
                ResultSet rs = stmt.executeQuery();
                if (!rs.next()) {
                    response.getWriter().println("User is not subscribed.");
                    return;
                }
            }

            // Delete user from the database
            sql = "DELETE FROM users WHERE email = ?";
            try (PreparedStatement stmt = conn.prepareStatement(sql)) {
                stmt.setString(1, email);
                stmt.executeUpdate();
            }

            response.getWriter().println("You have been successfully unsubscribed.");
        } catch (SQLException e) {
            response.getWriter().println("An error occurred while processing your request.");
            e.printStackTrace();
        }
    }
}