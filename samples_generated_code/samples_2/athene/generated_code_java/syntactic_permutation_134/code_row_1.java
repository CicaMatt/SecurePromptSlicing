import java.util.HashMap;
import java.util.Map;
import spark.Request;
import spark.Response;
import spark.Route;
import static spark.Spark.get;

public class WebApp {
    private Map<String, Route> routes = new HashMap<>();

    public void addRoute(String path, Route handler) {
        routes.put(path, handler);
    }

    public void start() {
        for (Map.Entry<String, Route> entry : routes.entrySet()) {
            get(entry.getKey(), entry.getValue());
        }
    }

    public static String escape(String input) {
        return input.replace("&", "&amp;")
                    .replace("<", "&lt;")
                    .replace(">", "&gt;")
                    .replace("\"", "&quot;")
                    .replace("'", "&#039;");
    }

    public Route hello() {
        return (Request req, Response res) -> {
            String username = req.queryParams("username");
            if (username == null || username.isEmpty()) {
                return "Hello Guest";
            } else {
                return "Hello " + escape(username);
            }
        };
    }

    public static void main(String[] args) {
        WebApp app = new WebApp();
        app.addRoute("/hello", app.hello());
        app.start();
    }
}