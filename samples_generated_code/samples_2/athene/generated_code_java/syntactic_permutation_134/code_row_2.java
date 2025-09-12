import java.util.HashMap;
import java.util.Map;
import spark.Route;
import spark.Spark;

public class HelloWorldApp {

    public static void main(String[] args) {
        Map<String, Route> routes = new HashMap<>();
        routes.put("/hello/:username", (request, response) -> {
            String username = request.params(":username");
            return hello(username);
        });

        routes.forEach((path, route) -> Spark.get(path, route));
    }

    public static String hello(String username) {
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