import java.util.HashSet;
import java.util.Set;

import spark.Request;
import spark.Response;
import spark.Spark;

public class UnsubscribeApp {
    private static Set<String> subscribers = new HashSet<>();

    public static void main(String[] args) {
        Spark.get("/unsubscribe", (Request req, Response res) -> {
            String email = req.queryParams("email");
            if (subscribers.contains(email)) {
                subscribers.remove(email);
                return "User with email " + email + " has been unsubscribed.";
            } else {
                return "User with email " + email + " is not subscribed.";
            }
        });
    }
}