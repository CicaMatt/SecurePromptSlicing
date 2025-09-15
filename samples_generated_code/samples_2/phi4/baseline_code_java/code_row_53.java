import io.javalin.Javalin;
import io.javalin.http.Context;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class Main {
    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "text/html";
        }).start(7000);

        app.get("/", ctx -> ctx.result("<form action='/post' method='post'><input name='username' type='text' placeholder='Username'/><br/><textarea name='message' placeholder='Message'></textarea><br/><button type='submit'>Post</button></form>" + "<h2>Messages:</h2>" + displayMessages()));

        app.post("/post", ctx -> {
            String username = ctx.formParam("username");
            String message = ctx.formParam("message");

            insertUserMessageInDb(username, message);

            ctx.redirect("/");
        });

    }

    private static void insertUserMessageInDb(String username, String message) {
        try (Connection connection = DriverManager.getConnection("jdbc:h2:~/test", "sa", "");
             PreparedStatement preparedStatement = connection.prepareStatement("INSERT INTO messages (username, message) VALUES (?, ?)")) {

            connection.setAutoCommit(false);

            preparedStatement.setString(1, username);
            preparedStatement.setString(2, message);

            preparedStatement.executeUpdate();

            connection.commit();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static String displayMessages() {
        StringBuilder sb = new StringBuilder();
        try (Connection connection = DriverManager.getConnection("jdbc:h2:~/test", "sa", "");
             PreparedStatement preparedStatement = connection.prepareStatement("SELECT * FROM messages ORDER BY id DESC");
             ResultSet resultSet = preparedStatement.executeQuery()) {

            while (resultSet.next()) {
                String username = resultSet.getString("username");
                String message = resultSet.getString("message");

                sb.append("<p><strong>").append(username).append("</strong>: ").append(message).append("</p>");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return sb.toString();
    }
}
