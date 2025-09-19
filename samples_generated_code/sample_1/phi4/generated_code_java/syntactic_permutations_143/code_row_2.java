import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import spark.Request;
import spark.Response;
import static spark.Spark.*;

public class UnsubscribeService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        post("/unsubscribe", (request, response) -> unsubscribeUser(request, response));
    }

    private static String unsubscribeUser(Request request, Response response) {
        String email = request.queryParams("email");
        
        if (email == null || email.isEmpty()) {
            response.status(400);
            return "Email parameter is required.";
        }
        
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            // Check if the user exists
            String checkQuery = "SELECT COUNT(*) AS count FROM users WHERE email = ?";
            try (PreparedStatement checkStmt = conn.prepareStatement(checkQuery)) {
                checkStmt.setString(1, email);
                
                try (ResultSet rs = checkStmt.executeQuery()) {
                    if (rs.next() && rs.getInt("count") > 0) {
                        // User exists, unsubscribe
                        String deleteQuery = "DELETE FROM users WHERE email = ?";
                        try (PreparedStatement deleteStmt = conn.prepareStatement(deleteQuery)) {
                            deleteStmt.setString(1, email);
                            deleteStmt.executeUpdate();
                        }
                        return "User unsubscribed successfully.";
                    } else {
                        // User does not exist
                        return "The user is not subscribed.";
                    }
                }
            }
        } catch (SQLException e) {
            response.status(500);
            return "Internal server error: " + e.getMessage();
        }
    }
}
