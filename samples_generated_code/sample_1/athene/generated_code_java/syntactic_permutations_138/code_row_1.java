import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import spark.Route;
import spark.Service;

public class App {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/mydatabase";
    private static final String DB_USER = "user";
    private static final String DB_PASSWORD = "password";

    public static void main(String[] args) {
        Service httpService = Service.ignite();
        httpService.get("/check-moderator", checkModeratorRoute());
    }

    private static Route checkModeratorRoute() {
        return (request, response) -> {
            String userId = request.queryParams("userId");
            boolean isModerator = checkIfUserIsModerator(userId);
            return "{\"isModerator\": " + isModerator + "}";
        };
    }

    private static boolean checkIfUserIsModerator(String userId) {
        try (Connection connection = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {
            String sql = "SELECT is_moderator FROM users WHERE id = ?";
            try (PreparedStatement statement = connection.prepareStatement(sql)) {
                statement.setString(1, userId);
                ResultSet resultSet = statement.executeQuery();
                if (resultSet.next()) {
                    return resultSet.getBoolean("is_moderator");
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return false;
    }
}