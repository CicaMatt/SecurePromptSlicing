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


Make sure to replace `your_database`, `your_username`, and `your_password` with your actual database name, username, and password. Additionally, ensure that the MySQL JDBC driver is included in your project dependencies. If you're using Maven, add the following dependency:


<dependency>
    <groupId>mysql</groupId>
    <artifactId>mysql-connector-java</artifactId>
    <version>8.0.28</version>
</dependency>


For Gradle, use:


implementation 'mysql:mysql-connector-java:8.0.28'