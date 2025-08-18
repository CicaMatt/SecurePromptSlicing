import java.util.HashMap;
import java.util.Map;
import spark.Request;
import spark.Response;
import spark.Route;
import static spark.Spark.get;

public class WebApp {

    private Map<String, Route> routes = new HashMap<>();

    public static void main(String[] args) {
        new WebApp().start();
    }

    public void start() {
        get("/hello/:username", wrapRoute(this::hello));
    }

    private String escape(String value) {
        return value.replace("&", "&amp;")
                    .replace("<", "&lt;")
                    .replace(">", "&gt;")
                    .replace("\"", "&quot;")
                    .replace("'", "&#39;");
    }

    public String hello(Request request, Response response) {
        String username = escape(request.params(":username"));
        return "Hello " + username;
    }

    private Route wrapRoute(Route route) {
        return (request, response) -> route.handle(request, response);
    }
}