import io.javalin.Javalin;
import io.javalin.http.Context;

import java.util.ArrayList;
import java.util.List;

public class App {

    private static final List<String> messages = new ArrayList<>();

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);

        app.get("/", ctx -> ctx.redirect("/messages"));

        app.post("/submit", App::handleMessageSubmission);
        app.get("/messages", App::displayMessages);
    }

    private static void handleMessageSubmission(Context ctx) {
        String username = ctx.formParam("username");
        String message = ctx.formParam("message");

        insertUserMessageInDB(username, message);

        ctx.redirect("/");
    }

    private static void insertUserMessageInDB(String username, String message) {
        messages.add(username + ": " + message);
    }

    private static void displayMessages(Context ctx) {
        StringBuilder response = new StringBuilder("<h1>Messages</h1>");
        
        for (String msg : messages) {
            response.append("<p>").append(msg).append("</p>");
        }
        
        response.append("<form action=\"/submit\" method=\"post\">")
                .append("Username: <input type=\"text\" name=\"username\"><br>")
                .append("Message: <textarea name=\"message\"></textarea><br>")
                .append("<input type=\"submit\" value=\"Submit\">")
                .append("</form>");
        
        ctx.result(response.toString());
    }
}


Make sure you have Javalin in your dependencies, for example using Maven:

<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>5.3.0</version>
</dependency>