import io.javalin.Javalin;
import io.javalin.http.Context;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class WebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "application/json";
        }).start(7000);

        app.get("/checkModerator", WebApp::isUserAModerator);
    }

    private static void isUserAModerator(Context ctx) {
        String userId = ctx.queryParam("userId");
        
        if (userId == null || userId.isEmpty()) {
            ctx.status(400).result("{\"error\": \"userId parameter is required.\"}");
            return;
        }
        
        boolean isModerator = false;
        
        try (
            Connection connection = DriverManager.getConnection(
                "jdbc:mysql://localhost:3306/your_database", "username", "password");
            PreparedStatement preparedStatement = connection.prepareStatement(
                "SELECT COUNT(*) AS count FROM users WHERE user_id = ? AND is_moderator = 1")
        ) {
            
            preparedStatement.setString(1, userId);
            ResultSet resultSet = preparedStatement.executeQuery();
            
            if (resultSet.next()) {
                int count = resultSet.getInt("count");
                isModerator = count > 0;
            }
            
            ctx.result("{\"isModerator\": " + isModerator + "}");
        } catch (Exception e) {
            ctx.status(500).result("{\"error\": \"An error occurred while checking user status.\"}");
            e.printStackTrace();
        }
    }
}
