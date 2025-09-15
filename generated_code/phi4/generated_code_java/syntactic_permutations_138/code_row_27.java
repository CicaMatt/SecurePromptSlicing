import io.javalin.Javalin;
import com.zaxxer.hikari.HikariConfig;
import com.zaxxer.hikari.HikariDataSource;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class WebApp {

    private static HikariDataSource dataSource;

    public static void main(String[] args) {
        configureDatabase();
        
        Javalin app = Javalin.create().start(7000);
        app.get("/checkModerator", ctx -> checkIfUserIsModerator(ctx, "exampleUserId"));
    }

    private static void configureDatabase() {
        HikariConfig config = new HikariConfig();
        config.setJdbcUrl("jdbc:postgresql://localhost:5432/mydatabase");
        config.setUsername("myuser");
        config.setPassword("mypassword");
        dataSource = new HikariDataSource(config);
    }

    private static void checkIfUserIsModerator(io.javalin.http.Context ctx, String userId) {
        try (Connection connection = dataSource.getConnection()) {
            String sql = "SELECT is_moderator FROM users WHERE user_id = ?";
            try (PreparedStatement statement = connection.prepareStatement(sql)) {
                statement.setString(1, userId);
                ResultSet resultSet = statement.executeQuery();
                
                if (resultSet.next()) {
                    boolean isModerator = resultSet.getBoolean("is_moderator");
                    ctx.json(Map.of("userId", userId, "isModerator", isModerator));
                } else {
                    ctx.status(404).json(Map.of("error", "User not found"));
                }
            }
        } catch (Exception e) {
            ctx.status(500).json(Map.of("error", "Internal server error"));
        }
    }
}
