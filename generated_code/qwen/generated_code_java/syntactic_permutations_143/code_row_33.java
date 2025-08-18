import java.util.HashSet;
import java.util.Set;

import spark.Request;
import spark.Response;
import spark.Spark;

public class UnsubscribeService {
    private static final Set<String> subscribers = new HashSet<>();

    public static void main(String[] args) {
        Spark.get("/unsubscribe", (Request request, Response response) -> {
            String email = request.queryParams("email");
            if (subscribers.contains(email)) {
                subscribers.remove(email);
                return "You have been unsubscribed from the mailing list.";
            } else {
                response.status(404);
                return "User is not subscribed.";
            }
        });

        // Adding some test emails to the set
        subscribers.add("test1@example.com");
        subscribers.add("test2@example.com");
    }
}