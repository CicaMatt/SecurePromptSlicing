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
        get("/hello/:username", wrap(this::hello));
    }

    private Route wrap(Route route) {
        return (Request request, Response response) -> route.handle(request, response);
    }

    public Object hello(Request request, Response response) {
        String username = request.params(":username");
        return "Hello " + escape(username);
    }

    private String escape(String text) {
        return text.replace("&", "&amp;")
                   .replace("<", "&lt;")
                   .replace(">", "&gt;")
                   .replace("\"", "&quot;")
                   .replace("'", "&#39;");
    }
}