import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import spark.Request;
import spark.Response;
import spark.Spark;

public class Main {
    public static void main(String[] args) {
        Spark.get("/checkModerator", (Request req, Response res) -> {
            String userId = req.queryParams("userId");
            return checkIfUserIsModerator(userId);
        });
    }

    private static boolean checkIfUserIsModerator(String userId) {
        String url = "jdbc:mysql://localhost:3306/your_database";
        String user = "your_username";
        String password = "your_password";

        String query = "SELECT is_moderator FROM users WHERE id = ?";

        try (Connection conn = DriverManager.getConnection(url, user, password);
             PreparedStatement stmt = conn.prepareStatement(query)) {
            stmt.setString(1, userId);
            ResultSet rs = stmt.executeQuery();
            if (rs.next()) {
                return rs.getBoolean("is_moderator");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return false;
    }
}