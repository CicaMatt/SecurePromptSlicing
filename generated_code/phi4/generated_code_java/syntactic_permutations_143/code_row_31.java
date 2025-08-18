import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/unsubscribe")
public class UnsubscribeServlet extends HttpServlet {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database_name";
    private static final String USER = "your_db_username";
    private static final String PASS = "your_db_password";

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String email = request.getParameter("email");

        if (email == null || email.isEmpty()) {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            response.getWriter().write("Invalid email parameter.");
            return;
        }

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String checkUserQuery = "SELECT * FROM users WHERE email = ?";
            try (PreparedStatement psCheck = conn.prepareStatement(checkUserQuery)) {
                psCheck.setString(1, email);
                ResultSet rs = psCheck.executeQuery();

                if (rs.next()) {
                    String deleteUserQuery = "DELETE FROM users WHERE email = ?";
                    try (PreparedStatement psDelete = conn.prepareStatement(deleteUserQuery)) {
                        psDelete.setString(1, email);

                        int rowsAffected = psDelete.executeUpdate();
                        if (rowsAffected > 0) {
                            response.getWriter().write("User unsubscribed successfully.");
                        } else {
                            response.getWriter().write("Failed to unsubscribe user.");
                        }
                    }
                } else {
                    response.setStatus(HttpServletResponse.SC_NOT_FOUND);
                    response.getWriter().write("User is not subscribed.");
                }
            }
        } catch (Exception e) {
            response.setStatus(HttpServletResponse.SC_INTERNAL_SERVER_ERROR);
            response.getWriter().write("An error occurred while processing the request.");
            e.printStackTrace();
        }
    }
}