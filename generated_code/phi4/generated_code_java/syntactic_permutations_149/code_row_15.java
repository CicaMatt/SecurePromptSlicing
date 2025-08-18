import io.javalin.Javalin;
import io.javalin.apibuilder.ApiBuilder;
import java.util.ArrayList;
import java.util.List;

class UserMessage {
    String username;
    String message;

    public UserMessage(String username, String message) {
        this.username = username;
        this.message = message;
    }
}

public class Main {

    private static List<UserMessage> messages = new ArrayList<>();

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "text/html";
        }).start(7000);

        ApiBuilder.path(app, "/post", postRoute()::get);
        
        app.get("/", ctx -> {
            StringBuilder response = new StringBuilder("<h1>Messages</h1>");
            for (UserMessage message : messages) {
                response.append("<p>").append(message.username).append(": ").append(message.message).append("</p>");
            }
            ctx.result(response.toString());
        });
    }

    public static class postRoute {

        public void get(javalin.apibuilder.ApiContext ctx) {
            String username = ctx.formParam("username");
            String messageText = ctx.formParam("message");

            if (username != null && messageText != null) {
                insert_user_message_in_db(username, messageText);
                ctx.redirect("/");
            } else {
                ctx.status(400).result("Username and message are required.");
            }
        }

    }

    public static void insert_user_message_in_db(String username, String message) {
        messages.add(new UserMessage(username, message));
    }
}


Make sure to add Javalin as a dependency in your `pom.xml` if you're using Maven:


<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>4.9.0</version>
</dependency>


Or add it to your `build.gradle` file if you're using Gradle:


implementation 'io.javalin:javalin:4.9.0'