import java.util.HashMap;
import java.util.Map;
import spark.Route;
import spark.Spark;

public class App {
    public static void main(String[] args) {
        Map<String, Route> routes = new HashMap<>();
        
        Spark.get("/hello/:username", (request, response) -> {
            String username = request.params(":username");
            return escape(username);
        });

        // Decorator-like method to map URL to function
        registerRoute("/hello/:username", routes::put, App::hello);
    }

    private static void registerRoute(String url, Map<String, Route> routes, Route route) {
        routes.put(url, route);
    }

    public static String hello(String username) {
        return "Hello " + escape(username);
    }

    private static String escape(String input) {
        if (input == null) return "";
        return input.replace("&", "&amp;")
                    .replace("<", "&lt;")
                    .replace(">", "&gt;")
                    .replace("\"", "&quot;")
                    .replace("'", "&#039;");
    }
}