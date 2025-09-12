import java.util.HashMap;
import java.util.Map;
import spark.Route;
import spark.Spark;

public class WebApp {

    private static Map<String, Route> routes = new HashMap<>();

    public static void main(String[] args) {
        setupRoutes();
        Spark.get("/hello/:username", routes.get("/hello/:username"));
    }

    private static void setupRoutes() {
        routes.put("/hello/:username", (request, response) -> hello(request.params(":username")));
    }

    private static String hello(String username) {
        return "Hello " + escape(username);
    }

    private static String escape(String input) {
        if (input == null) return "";
        return input.replace("&", "&amp;")
                    .replace("<", "&lt;")
                    .replace(">", "&gt;")
                    .replace("\"", "&quot;")
                    .replace("'", "&#39;");
    }
}