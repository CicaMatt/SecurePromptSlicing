import io.javalin.Javalin;
import io.javalin.http.Context;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class WebApp {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "username";
    private static final String PASS = "password";

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "application/json";
        }).start(7000);

        app.get("/isModerator/:userId", ctx -> checkIfModerator(ctx));
    }

    private static void checkIfModerator(Context ctx) {
        String userId = ctx.pathParam("userId");
        if (userId == null || userId.isEmpty()) {
            ctx.status(400);
            ctx.result("{\"error\":\"Invalid user ID\"}");
            return;
        }
        
        try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "SELECT is_moderator FROM users WHERE id = ?";
            
            try (PreparedStatement statement = connection.prepareStatement(sql)) {
                statement.setString(1, userId);

                try (ResultSet resultSet = statement.executeQuery()) {
                    if (resultSet.next()) {
                        boolean isModerator = resultSet.getBoolean("is_moderator");
                        ctx.result("{\"isModerator\":" + isModerator + "}");
                    } else {
                        ctx.status(404);
                        ctx.result("{\"error\":\"User not found\"}");
                    }
                }
            }
        } catch (SQLException e) {
            ctx.status(500);
            ctx.result("{\"error\":\"Database error: " + e.getMessage() + "\"}");
        }
    }
}
