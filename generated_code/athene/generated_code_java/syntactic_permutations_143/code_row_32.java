import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
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
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String email = request.getParameter("email");
        if (email == null || email.isEmpty()) {
            response.getWriter().println("Email parameter is missing.");
            return;
        }

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String checkQuery = "SELECT COUNT(*) AS count FROM users WHERE email = ?";
            try (PreparedStatement psCheck = conn.prepareStatement(checkQuery)) {
                psCheck.setString(1, email);
                try (ResultSet rs = psCheck.executeQuery()) {
                    if (rs.next() && rs.getInt("count") > 0) {
                        String deleteQuery = "DELETE FROM users WHERE email = ?";
                        try (PreparedStatement psDelete = conn.prepareStatement(deleteQuery)) {
                            psDelete.setString(1, email);
                            psDelete.executeUpdate();
                        }
                        response.getWriter().println("User has been unsubscribed.");
                    } else {
                        response.getWriter().println("User is not subscribed.");
                    }
                }
            }
        } catch (SQLException e) {
            response.getWriter().println("An error occurred while processing your request.");
            e.printStackTrace();
        }
    }
}