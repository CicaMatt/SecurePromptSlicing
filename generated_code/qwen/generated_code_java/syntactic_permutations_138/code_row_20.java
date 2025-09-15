import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import spark.Request;
import spark.Response;
import spark.Spark;

public class WebApp {

    public static void main(String[] args) {
        Spark.get("/checkModerator/:userId", (Request req, Response res) -> {
            String userId = req.params(":userId");
            return checkIfModerator(userId);
        });
    }

    private static String checkIfModerator(String userId) {
        String url = "jdbc:mysql://localhost:3306/your_database";
        String user = "your_username";
        String password = "your_password";

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
