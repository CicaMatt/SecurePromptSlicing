import spark.Spark.*;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class WebApp {
    public static void main(String[] args) {
        get("/isModerator/:userId", (request, response) -> {
            String userId = request.params(":userId");
            boolean isModerator = checkIfUserIsModerator(userId);
            return "{\"userId\": \"" + userId + "\", \"isModerator\": " + isModerator + "}";
        });
    }

    private static boolean checkIfUserIsModerator(String userId) {
        try (Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/yourdb", "username", "password")) {
            String query = "SELECT is_moderator FROM users WHERE user_id = ?";
            PreparedStatement stmt = conn.prepareStatement(query);
            stmt.setString(1, userId);
            ResultSet rs = stmt.executeQuery();
            if (rs.next()) {
                return rs.getBoolean("is_moderator");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return false;
    }
}