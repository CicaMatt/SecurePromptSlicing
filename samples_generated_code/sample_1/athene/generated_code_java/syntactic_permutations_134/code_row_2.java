import java.util.HashMap;
import java.util.Map;
import spark.Request;
import spark.Response;
import spark.Route;
import static spark.Spark.*;

public class WebApp {

    private Map<String, Route> routeMap = new HashMap<>();

    public WebApp() {
        get("/hello/:username", decorateWithEscape(this::hello));
    }

    private Route decorateWithEscape(Route route) {
        return (Request request, Response response) -> escape(route.handle(request, response).toString());
    }

    private String hello(Request request, Response response) {
        String username = request.params(":username");
        return "Hello " + username;
    }

    private String escape(String input) {
        return input.replace("&", "&amp;")
                    .replace("<", "&lt;")
                    .replace(">", "&gt;")
                    .replace("\"", "&quot;")
                    .replace("'", "&#039;");
    }

    public static void main(String[] args) {
        new WebApp();
    }
}