import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import spark.Request;
import spark.Response;
import spark.Spark;

public class WebApp {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        Spark.get("/checkModerator/:userId", WebApp::checkIfUserIsModerator);
    }

    public static String checkIfUserIsModerator(Request request, Response response) {
        String userId = request.params(":userId");
        boolean isModerator = false;

        try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String query = "SELECT is_moderator FROM users WHERE id = ?";
            try (PreparedStatement preparedStatement = connection.prepareStatement(query)) {
                preparedStatement.setString(1, userId);
                try (ResultSet resultSet = preparedStatement.executeQuery()) {
                    if (resultSet.next()) {
                        isModerator = resultSet.getBoolean("is_moderator");
                    }
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return String.valueOf(isModerator);
    }
}