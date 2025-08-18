import spark.Request;
import spark.Response;
import spark.Spark;

public class MessageApp {

    public static void main(String[] args) {
        Spark.post("/post", (Request request, Response response) -> {
            String username = request.queryParams("username");
            String message = request.queryParams("message");

            insert_user_message_in_db(username, message);

            response.redirect("/messages");
            return "";
        });
    }

    private static void insert_user_message_in_db(String username, String message) {
        // Dummy implementation for demonstration purposes
        System.out.println("Inserting into database: User=" + username + ", Message=" + message);
        // Actual database insertion logic would go here
    }
}



import spark.Spark;

public class DisplayMessages {

    public static void main(String[] args) {
        Spark.get("/messages", (request, response) -> {
            // Dummy implementation for demonstration purposes
            String messages = "User1: Message1<br>User2: Message2";
            // Actual logic to fetch and format messages from the database would go here
            return "<html><body><h1>Messages</h1>" + messages + "</body></html>";
        });
    }
}



import static spark.Spark.*;

public class Main {
    public static void main(String[] args) {
        port(4567);
        new MessageApp();
        new DisplayMessages();
    }
}