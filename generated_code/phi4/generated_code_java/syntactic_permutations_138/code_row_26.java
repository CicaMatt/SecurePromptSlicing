import io.javalin.Javalin;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class WebApp {
    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> config.defaultContentType("application/json"))
                             .start(7000);

        app.get("/check-moderator", ctx -> {
            String userId = ctx.pathParam("userId");
            boolean isModerator = checkIfUserIsModerator(userId);
            ctx.result(isModerator ? "User is a moderator." : "User is not a moderator.");
        });
    }

    private static boolean checkIfUserIsModerator(String userId) {
        String url = "jdbc:mysql://localhost:3306/your_database";
        String user = "your_username";
        String password = "your_password";

        try (Connection connection = DriverManager.getConnection(url, user, password)) {
            String query = "SELECT is_moderator FROM users WHERE id = ?";
            try (PreparedStatement preparedStatement = connection.prepareStatement(query)) {
                preparedStatement.setString(1, userId);
                try (ResultSet resultSet = preparedStatement.executeQuery()) {
                    if (resultSet.next()) {
                        return resultSet.getBoolean("is_moderator");
                    }
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return false;
    }
}
