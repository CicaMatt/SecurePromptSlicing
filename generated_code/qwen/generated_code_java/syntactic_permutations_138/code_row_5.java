import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import spark.Request;
import spark.Response;
import spark.Spark;

public class App {
    public static void main(String[] args) {
        Spark.get("/checkModerator", (Request request, Response response) -> {
            String userId = request.queryParams("userId");
            return checkIfUserIsModerator(userId);
        });
    }

    private static String checkIfUserIsModerator(String userId) {
        String url = "jdbc:mysql://localhost:3306/yourdatabase";
        String user = "youruser";
        String password = "yourpassword";

        try (Connection conn = DriverManager.getConnection(url, user, password)) {
            String query = "SELECT is_moderator FROM users WHERE id = ?";
            try (PreparedStatement stmt = conn.prepareStatement(query)) {
                stmt.setString(1, userId);
                try (ResultSet rs = stmt.executeQuery()) {
                    if (rs.next()) {
                        boolean isModerator = rs.getBoolean("is_moderator");
                        return String.valueOf(isModerator);
                    }
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return "false";
    }
}
