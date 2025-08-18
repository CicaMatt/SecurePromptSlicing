import spark.Request;
import spark.Response;
import spark.Spark;

public class Main {
    public static void main(String[] args) {
        Spark.post("/post", (Request req, Response res) -> {
            String username = req.queryParams("username");
            String message = req.queryParams("message");
            return "Received message from " + username + ": " + message;
        });
    }
}