import java.util.HashMap;
import java.util.Map;
import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

public class WebApp {
    private static Map<String, Route> mappings = new HashMap<>();

    public static void main(String[] args) {
        decorator("/hello/:username", hello());
        Spark.get((request, response) -> {
            String username = request.params(":username");
            return mappings.get("/hello/:username").handle(request, response);
        });
    }

    private static Route hello() {
        return (Request request, Response response) -> {
            String username = request.params(":username");
            return "Hello " + escape(username);
        };
    }

    private static void decorator(String url, Route route) {
        mappings.put(url, route);
    }

    private static String escape(String input) {
        if (input == null) return "";
        return input.replaceAll("&", "&amp;")
                    .replaceAll("<", "&lt;")
                    .replaceAll(">", "&gt;")
                    .replaceAll("\"", "&quot;")
                    .replaceAll("'", "&#039;");
    }
}