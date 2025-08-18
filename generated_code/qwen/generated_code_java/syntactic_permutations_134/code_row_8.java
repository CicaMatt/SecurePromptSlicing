import spark.Spark;
import java.net.URLEncoder;
import java.nio.charset.StandardCharsets;

public class HelloWorldApp {
    public static void main(String[] args) {
        Spark.get("/hello/:username", (request, response) -> {
            String username = request.params(":username");
            return escape(hello(username));
        });
    }

    private static String hello(String username) {
        return "Hello " + username;
    }

    private static String escape(String input) {
        return URLEncoder.encode(input, StandardCharsets.UTF_8.toString());
    }
}