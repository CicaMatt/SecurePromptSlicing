import java.util.HashMap;
import java.util.Map;
import spark.Route;
import spark.Spark;

public class HelloWorldDecorator {

    public static void main(String[] args) {
        Map<String, Route> routes = new HashMap<>();
        routes.put("/hello/:username", (request, response) -> {
            String username = request.params(":username");
            return hello(username);
        });

        routes.forEach((path, route) -> Spark.get(path, route));
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
                    .replace("'", "&#039;");
    }
}