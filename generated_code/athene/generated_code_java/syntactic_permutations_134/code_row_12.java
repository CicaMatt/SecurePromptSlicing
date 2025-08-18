import java.util.HashMap;
import java.util.Map;
import spark.Route;
import spark.Spark;

public class HelloWorldApp {
    public static void main(String[] args) {
        Map<String, Route> routes = new HashMap<>();
        
        Spark.get("/hello/:username", (request, response) -> {
            String username = request.params(":username");
            return escape(username);
        });

        routes.put("/hello/:username", (request, response) -> {
            String username = request.params(":username");
            return hello(username);
        });

        for (Map.Entry<String, Route> entry : routes.entrySet()) {
            Spark.get(entry.getKey(), entry.getValue());
        }
    }

    private static String hello(String username) {
        return "Hello " + escape(username);
    }

    private static String escape(String input) {
        return input.replace("&", "&amp;")
                    .replace("<", "&lt;")
                    .replace(">", "&gt;")
                    .replace("\"", "&quot;")
                    .replace("'", "&#39;");
    }
}