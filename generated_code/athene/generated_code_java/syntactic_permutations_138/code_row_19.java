import spark.Spark.*;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class WebApp {
    public static void main(String[] args) {
        get("/isModerator", (request, response) -> {
            String userId = request.queryParams("userId");
            return isUserModerator(userId);
        });
    }

    private static boolean isUserModerator(String userId) {
        try (Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/yourdb", "user", "password")) {
            String sql = "SELECT is_moderator FROM users WHERE id = ?";
            try (PreparedStatement stmt = conn.prepareStatement(sql)) {
                stmt.setString(1, userId);
                try (ResultSet rs = stmt.executeQuery()) {
                    if (rs.next()) {
                        return rs.getBoolean("is_moderator");
                    }
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return false;
    }
}