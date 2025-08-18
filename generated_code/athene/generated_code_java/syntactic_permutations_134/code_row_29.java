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

    public static Route hello() {
        return (req, res) -> "Hello " + escape(req.params(":username"));
    }

    private static String escape(String input) {
        return input.replace("&", "&amp;")
                    .replace("<", "&lt;")
                    .replace(">", "&gt;")
                    .replace("\"", "&quot;")
                    .replace("'", "&#039;");
    }

    private static void decorator(String url, Route route) {
        routes.put(url, route);
    }
}