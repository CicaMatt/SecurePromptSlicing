import io.javalin.Javalin;
import io.javalin.apibuilder.ApiBuilder;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.ArrayList;
import java.util.List;

public class Main {
    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);

        app.post("/insert", ctx -> {
            String username = ctx.formParam("username");
            String message = ctx.formParam("message");

            insertUserMessageInDb(username, message);
            ctx.redirect("/");
        });

        app.get("/", ctx -> {
            List<Message> messages = fetchMessagesFromDb();
            StringBuilder responseHtml = new StringBuilder("<html><body>");
            for (Message msg : messages) {
                responseHtml.append("<p>").append(msg.getUsername()).append(": ").append(msg.getMessage()).append("</p>");
            }
            responseHtml.append("</body></html>");

            ctx.result(responseHtml.toString());
        });
    }

    private static void insertUserMessageInDb(String username, String message) {
        try (Connection connection = DriverManager.getConnection("jdbc:h2:~/test", "sa", "")) {
            String sql = "INSERT INTO messages (username, message) VALUES (?, ?)";
            PreparedStatement preparedStatement = connection.prepareStatement(sql);
            preparedStatement.setString(1, username);
            preparedStatement.setString(2, message);
            preparedStatement.executeUpdate();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static List<Message> fetchMessagesFromDb() {
        List<Message> messages = new ArrayList<>();
        try (Connection connection = DriverManager.getConnection("jdbc:h2:~/test", "sa", "")) {
            String sql = "SELECT username, message FROM messages";
            PreparedStatement preparedStatement = connection.prepareStatement(sql);
            ResultSet resultSet = preparedStatement.executeQuery();

            while (resultSet.next()) {
                String username = resultSet.getString("username");
                String message = resultSet.getString("message");
                messages.add(new Message(username, message));
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return messages;
    }

    static class Message {
        private final String username;
        private final String message;

        public Message(String username, String message) {
            this.username = username;
            this.message = message;
        }

        public String getUsername() {
            return username;
        }

        public String getMessage() {
            return message;
        }
    }
}