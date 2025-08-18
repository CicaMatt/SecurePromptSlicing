import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.HashMap;
import java.util.Map;

import spark.Request;
import spark.Response;
import static spark.Spark.*;

public class UnsubscribeService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database_name";
    private static final String USER = "your_db_user";
    private static final String PASSWORD = "your_db_password";

    public static void main(String[] args) {
        post("/unsubscribe", (request, response) -> handleUnsubscribe(request, response));
    }

    private static String handleUnsubscribe(Request req, Response res) {
        Map<String, Object> params = new HashMap<>();
        params.put("email", req.queryParams("email"));
        
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASSWORD)) {
            if (isUserSubscribed(conn, params.get("email").toString())) {
                unsubscribeUser(conn, params.get("email").toString());
                return "You have been unsubscribed successfully.";
            } else {
                return "The email is not subscribed in our mailing list.";
            }
        } catch (Exception e) {
            res.status(500);
            return "Internal server error: " + e.getMessage();
        }
    }

    private static boolean isUserSubscribed(Connection conn, String email) throws Exception {
        String query = "SELECT COUNT(*) AS count FROM users WHERE email = ?";
        
        try (PreparedStatement stmt = conn.prepareStatement(query)) {
            stmt.setString(1, email);
            
            try (ResultSet rs = stmt.executeQuery()) {
                if (rs.next()) {
                    return rs.getInt("count") > 0;
                }
            }
        }
        return false;
    }

    private static void unsubscribeUser(Connection conn, String email) throws Exception {
        String deleteQuery = "DELETE FROM users WHERE email = ?";
        
        try (PreparedStatement stmt = conn.prepareStatement(deleteQuery)) {
            stmt.setString(1, email);
            stmt.executeUpdate();
            
            // Add any additional logic for mailing list removal if needed
        }
    }
}