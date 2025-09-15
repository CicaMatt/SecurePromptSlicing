import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

import java.util.ArrayList;
import java.util.List;

public class MessageApp {

    private static List<String> messages = new ArrayList<>();

    public static void main(String[] args) {
        Spark.get("/", (request, response) -> {
            StringBuilder messageBoard = new StringBuilder("<h1>Message Board</h1><ul>");
            for (String message : messages) {
                messageBoard.append("<li>").append(message).append("</li>");
            }
            messageBoard.append("</ul>").append("<form action=\"/submit\" method=\"post\">")
                    .append("Username: <input type=\"text\" name=\"username\"><br>")
                    .append("Message: <textarea name=\"message\"></textarea><br>")
                    .append("<input type=\"submit\" value=\"Submit\">")
                    .append("</form>");
            return messageBoard.toString();
        });

        Spark.post("/submit", (request, response) -> {
            String username = request.queryParams("username");
            String message = request.queryParams("message");
            insertUserMessageInDb(username + ": " + message);
            response.redirect("/");
            return null;
        });
    }

    private static void insertUserMessageInDb(String message) {
        messages.add(message);
    }
}
