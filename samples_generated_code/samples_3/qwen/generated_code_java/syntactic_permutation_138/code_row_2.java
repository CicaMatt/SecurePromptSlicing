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
        Spark.get("/checkModerator", WebApp::checkModerator);
    }

    private static String checkModerator(Request req, Response res) {
        String userId = req.queryParams("userId");
        if (userId == null || userId.isEmpty()) {
            res.status(400);
            return "User ID is required.";
        }

        boolean isModerator = false;
        try (Connection connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/yourdatabase", "username", "password");
             PreparedStatement statement = connection.prepareStatement("SELECT is_moderator FROM users WHERE id = ?")) {
            statement.setString(1, userId);
            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                isModerator = resultSet.getBoolean("is_moderator");
            }
        } catch (SQLException e) {
            res.status(500);
            return "Database error: " + e.getMessage();
        }

        res.type("application/json");
        return "{\"isModerator\": " + isModerator + "}";
    }
}
