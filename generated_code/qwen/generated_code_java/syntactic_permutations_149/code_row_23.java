import spark.Request;
import spark.Response;
import spark.Spark;

public class MessageApp {
    public static void main(String[] args) {
        Spark.post("/post", (Request request, Response response) -> {
            String username = request.queryParams("username");
            String message = request.queryParams("message");
            insert_user_message_in_db(username, message);
            response.redirect("/");
            return null;
        });
    }

    private static void insert_user_message_in_db(String username, String message) {
        // Dummy implementation for demonstration purposes
        System.out.println("Inserting into database: User - " + username + ", Message - " + message);
    }
}
