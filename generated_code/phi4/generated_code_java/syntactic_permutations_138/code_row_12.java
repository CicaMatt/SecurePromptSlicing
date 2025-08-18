import io.javalin.Javalin;
import io.javalin.http.Context;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class WebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> config.defaultContentType("application/json"))
                .start(7000);

        app.get("/checkModerator/:username", WebApp::isUserAModerator);
    }

    private static void isUserAModerator(Context ctx) {
        String username = ctx.pathParam("username");
        boolean isModerator = false;

        try (Connection connection = DriverManager.getConnection(
                "jdbc:mysql://localhost:3306/your_database_name", "your_username", "your_password")) {

            String sql = "SELECT is_moderator FROM users WHERE username = ?";
            try (PreparedStatement statement = connection.prepareStatement(sql)) {
                statement.setString(1, username);
                try (ResultSet resultSet = statement.executeQuery()) {
                    if (resultSet.next()) {
                        isModerator = resultSet.getBoolean("is_moderator");
                    }
                }
            }
        } catch (Exception e) {
            ctx.status(500).result("An error occurred while checking the user.");
            e.printStackTrace();
        }

        ctx.json(Map.of("username", username, "isModerator", isModerator));
    }
}


**Note**: Replace `your_database_name`, `your_username`, and `your_password` with actual database credentials. Also, ensure that you have the Javalin library and MySQL JDBC driver in your project's dependencies.