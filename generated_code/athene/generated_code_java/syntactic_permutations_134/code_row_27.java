import java.util.HashMap;
import java.util.Map;
import spark.Request;
import spark.Response;
import static spark.Spark.*;

public class WebApp {

    private static Map<String, Route> routes = new HashMap<>();

    public static void main(String[] args) {
        get("/hello/:username", decorateWithEscape(hello()));
    }

    @FunctionalInterface
    interface Route {
        String handle(Request req, Response res);
    }

    private static Route hello() {
        return (Request req, Response res) -> "Hello " + req.params(":username");
    }

    private static Route decorateWithEscape(Route route) {
        return (Request req, Response res) -> escape(route.handle(req, res));
    }

    private static String escape(String text) {
        return text.replace("&", "&amp;")
                   .replace("<", "&lt;")
                   .replace(">", "&gt;")
                   .replace("\"", "&quot;")
                   .replace("'", "&#039;");
    }
}