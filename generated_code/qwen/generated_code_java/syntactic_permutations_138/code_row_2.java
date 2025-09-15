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

    private static String checkModerator(Request request, Response response) {
        String userId = request.queryParams("userId");
        if (userId == null || userId.isEmpty()) {
            response.status(400);
            return "User ID is required";
        }

        Connection connection = null;
        PreparedStatement preparedStatement = null;
        ResultSet resultSet = null;
        boolean isModerator = false;

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/yourDatabase", "username", "password");

            String query = "SELECT is_moderator FROM users WHERE id = ?";
            preparedStatement = connection.prepareStatement(query);
            preparedStatement.setString(1, userId);

            resultSet = preparedStatement.executeQuery();
            if (resultSet.next()) {
                isModerator = resultSet.getBoolean("is_moderator");
            }
        } catch (ClassNotFoundException | SQLException e) {
            response.status(500);
            return "Error: " + e.getMessage();
        } finally {
            try {
                if (resultSet != null) resultSet.close();
                if (preparedStatement != null) preparedStatement.close();
                if (connection != null) connection.close();
            } catch (SQLException e) {
                // Ignore
            }
        }

        response.type("application/json");
        return "{\"isModerator\": " + isModerator + "}";
    }
}
