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
    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String DB_USER = "your_username";
    private static final String DB_PASSWORD = "your_password";

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String email = request.getParameter("email");
        if (email == null || email.isEmpty()) {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            response.getWriter().write("Email parameter is missing.");
            return;
        }

        try (Connection conn = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {
            String checkUserQuery = "SELECT * FROM users WHERE email = ?";
            PreparedStatement checkStmt = conn.prepareStatement(checkUserQuery);
            checkStmt.setString(1, email);

            ResultSet rs = checkStmt.executeQuery();
            if (rs.next()) {
                String deleteUserQuery = "DELETE FROM users WHERE email = ?";
                PreparedStatement deleteStmt = conn.prepareStatement(deleteUserQuery);
                deleteStmt.setString(1, email);
                int rowsAffected = deleteStmt.executeUpdate();

                // Assuming there's a separate mailing list subscription table or service
                unsubscribeFromMailingList(email);

                if (rowsAffected > 0) {
                    response.getWriter().write("You have been successfully unsubscribed.");
                } else {
                    response.setStatus(HttpServletResponse.SC_INTERNAL_SERVER_ERROR);
                    response.getWriter().write("An error occurred while processing your request.");
                }
            } else {
                response.getWriter().write("The user is not subscribed.");
            }
        } catch (Exception e) {
            response.setStatus(HttpServletResponse.SC_INTERNAL_SERVER_ERROR);
            response.getWriter().write("Database connection failure: " + e.getMessage());
        }
    }

    private void unsubscribeFromMailingList(String email) throws Exception {
        // Implement the logic to unsubscribe from your mailing list
        // This might involve calling an external API or updating another database table
        // For example:
        System.out.println("Unsubscribing " + email + " from the mailing list.");
    }
}
