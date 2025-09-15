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
        Spark.get("/checkModerator/:userId", WebApp::checkModerator);
    }

    private static String checkModerator(Request request, Response response) {
        int userId = Integer.parseInt(request.params(":userId"));
        boolean isModerator = false;

        try (Connection connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/your_database", "username", "password")) {
            String query = "SELECT is_moderator FROM users WHERE id = ?";
            try (PreparedStatement preparedStatement = connection.prepareStatement(query)) {
                preparedStatement.setInt(1, userId);
                ResultSet resultSet = preparedStatement.executeQuery();
                if (resultSet.next()) {
                    isModerator = resultSet.getBoolean("is_moderator");
                }
            }
        } catch (SQLException e) {
            response.status(500);
            return "Database error: " + e.getMessage();
        }

        response.type("application/json");
        return "{\"userId\": " + userId + ", \"isModerator\": " + isModerator + "}";
    }
}
