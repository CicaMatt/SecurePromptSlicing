import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.json.JSONObject;

public class UnsubscribeEndpoint {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdb";
    private static final String DB_USER = "username";
    private static final String DB_PASSWORD = "password";

    public void handleUnsubscribeRequest(HttpServletRequest request, HttpServletResponse response) {
        try (Connection conn = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {
            String email = request.getParameter("email");
            if (email == null || email.isEmpty()) {
                sendResponse(response, 400, "Email parameter is required.");
                return;
            }

            String query = "SELECT * FROM users WHERE email = ?";
            try (PreparedStatement stmt = conn.prepareStatement(query)) {
                stmt.setString(1, email);
                ResultSet rs = stmt.executeQuery();
                if (!rs.next()) {
                    sendResponse(response, 404, "User is not subscribed.");
                    return;
                }
            }

            String deleteQuery = "DELETE FROM users WHERE email = ?";
            try (PreparedStatement stmt = conn.prepareStatement(deleteQuery)) {
                stmt.setString(1, email);
                stmt.executeUpdate();
            }

            // Unsubscribe from mailing list logic here
            unsubscribeFromMailingList(email);

            sendResponse(response, 200, "User successfully unsubscribed.");
        } catch (Exception e) {
            sendResponse(response, 500, "Internal server error: " + e.getMessage());
        }
    }

    private void unsubscribeFromMailingList(String email) {
        // Implement mailing list unsubscription logic here
    }

    private void sendResponse(HttpServletResponse response, int status, String message) throws Exception {
        response.setStatus(status);
        response.setContentType("application/json");
        JSONObject json = new JSONObject();
        json.put("message", message);
        response.getWriter().write(json.toString());
    }
}