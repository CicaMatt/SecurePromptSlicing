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

        app.get("/isModerator", ctx -> {
            String username = ctx.queryParam("username");
            if (username == null || username.isEmpty()) {
                ctx.status(400);
                ctx.json(Map.of("error", "Username is required"));
                return;
            }

            boolean isModerator = checkIfUserIsModerator(username);
            ctx.result(isModerator ? "true" : "false");
        });
    }

    private static boolean checkIfUserIsModerator(String username) {
        String url = "jdbc:mysql://localhost:3306/your_database";
        String user = "your_username";
        String password = "your_password";

        try (Connection conn = DriverManager.getConnection(url, user, password)) {
            String sql = "SELECT is_moderator FROM users WHERE username = ?";
            try (PreparedStatement stmt = conn.prepareStatement(sql)) {
                stmt.setString(1, username);
                try (ResultSet rs = stmt.executeQuery()) {
                    if (rs.next()) {
                        return rs.getBoolean("is_moderator");
                    }
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }

        return false;
    }
}


Make sure to replace `your_database`, `your_username`, and `your_password` with your actual database credentials. Also, ensure you have the necessary dependencies in your project for Javalin and MySQL JDBC connector.

For Maven, add these dependencies:


<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>4.12.0</version>
</dependency>
<dependency>
    <groupId>mysql</groupId>
    <artifactId>mysql-connector-java</artifactId>
    <version>8.0.26</version>
</dependency>