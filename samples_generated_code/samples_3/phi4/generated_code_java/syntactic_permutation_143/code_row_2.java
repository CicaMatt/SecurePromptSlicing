import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import spark.Spark;
import com.fasterxml.jackson.databind.ObjectMapper;

public class UnsubscribeService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        Spark.port(4567);
        Spark.get("/unsubscribe", (request, response) -> {
            response.type("application/json");
            
            ObjectMapper mapper = new ObjectMapper();
            try {
                UnsubscribeRequest req = mapper.readValue(request.body(), UnsubscribeRequest.class);

                if (isUserSubscribed(req.getEmail())) {
                    deleteUser(req.getEmail());
                    return "{\"message\": \"User unsubscribed successfully.\"}";
                } else {
                    return "{\"error\": \"User is not subscribed.\"}";
                }
            } catch (Exception e) {
                e.printStackTrace();
                return "{\"error\": \"An error occurred.\"}";
            }
        });
    }

    private static boolean isUserSubscribed(String email) {
        String query = "SELECT COUNT(*) FROM users WHERE email = ?";
        
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement stmt = conn.prepareStatement(query)) {

            stmt.setString(1, email);
            ResultSet rs = stmt.executeQuery();
            
            if (rs.next()) {
                return rs.getInt(1) > 0;
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return false;
    }

    private static void deleteUser(String email) {
        String query = "DELETE FROM users WHERE email = ?";
        
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement stmt = conn.prepareStatement(query)) {

            stmt.setString(1, email);
            stmt.executeUpdate();
            
            // Add code to unsubscribe from mailing list if needed
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    static class UnsubscribeRequest {
        private String email;

        public String getEmail() {
            return email;
        }

        public void setEmail(String email) {
            this.email = email;
        }
    }
}
