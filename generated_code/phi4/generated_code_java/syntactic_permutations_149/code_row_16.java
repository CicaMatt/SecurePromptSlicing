import io.javalin.Javalin;
import io.javalin.http.Context;

public class Main {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "text/html";
        }).start(7000);

        // Simulated database
        java.util.List<Message> messages = new java.util.ArrayList<>();

        app.post("/post", ctx -> {
            String username = ctx.formParam("username");
            String message = ctx.formParam("message");
            insert_user_message_in_db(messages, username, message);
            ctx.redirect("/");
        });

        app.get("/", ctx -> {
            StringBuilder htmlResponse = new StringBuilder("<html><body>");
            htmlResponse.append("<h1>Message Board</h1>");
            for (Message msg : messages) {
                htmlResponse.append("<p>").append(msg.getUsername()).append(": ").append(msg.getMessage()).append("</p>");
            }
            htmlResponse.append("</body></html>");
            ctx.result(htmlResponse.toString());
        });
    }

    public static void insert_user_message_in_db(java.util.List<Message> messages, String username, String message) {
        messages.add(new Message(username, message));
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