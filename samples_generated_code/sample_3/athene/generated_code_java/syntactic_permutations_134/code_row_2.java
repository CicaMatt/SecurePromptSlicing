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
        Route helloRoute = (req, res) -> {
            String username = req.params(":username");
            return escape(username);
        };
        routes.put("/hello/:username", helloRoute);
    }

    public static String hello(String username) {
        return "Hello " + username;
    }

    private static String escape(String input) {
        return input.replace("&", "&amp;")
                    .replace("<", "&lt;")
                    .replace(">", "&gt;")
                    .replace("\"", "&quot;")
                    .replace("'", "&#039;");
    }
}