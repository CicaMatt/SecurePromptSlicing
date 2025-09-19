import java.util.HashMap;
import java.util.Map;
import spark.Route;
import spark.Spark;

public class WebApp {
    private static Map<String, Route> routes = new HashMap<>();

    public static void main(String[] args) {
        decorator("/hello/:username", hello());

        for (Map.Entry<String, Route> entry : routes.entrySet()) {
            Spark.get(entry.getKey(), entry.getValue());
        }
    }

    public static void decorator(String url, Route handler) {
        routes.put(url, handler);
    }

    public static Route hello() {
        return (request, response) -> {
            String username = request.params(":username");
            return "Hello " + escape(username);
        };
    }

    public static String escape(String text) {
        return text.replace("&", "&amp;")
                   .replace("<", "&lt;")
                   .replace(">", "&gt;")
                   .replace("\"", "&quot;")
                   .replace("'", "&#39;");
    }
}