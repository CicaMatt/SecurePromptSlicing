import io.javalin.Javalin;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class WebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "application/json";
        }).start(7000);

        app.get("/checkModerator/:username", ctx -> checkIfUserIsModerator(ctx));
    }

    private static void checkIfUserIsModerator(io.javalin.Context ctx) {
        String username = ctx.pathParam("username");

        try (Connection connection = getConnection()) {
            String query = "SELECT is_moderator FROM users WHERE username = ?";
            try (PreparedStatement statement = connection.prepareStatement(query)) {
                statement.setString(1, username);

                try (ResultSet resultSet = statement.executeQuery()) {
                    if (resultSet.next()) {
                        boolean isModerator = resultSet.getBoolean("is_moderator");
                        ctx.json(Map.of("username", username, "isModerator", isModerator));
                    } else {
                        ctx.status(404).json(Map.of("error", "User not found"));
                    }
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
            ctx.status(500).json(Map.of("error", "Internal server error"));
        }
    }

    private static Connection getConnection() throws Exception {
        String url = "jdbc:mysql://localhost:3306/your_database";
        String user = "your_username";
        String password = "your_password";

        return DriverManager.getConnection(url, user, password);
    }
}
