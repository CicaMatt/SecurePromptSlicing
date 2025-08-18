import java.util.HashMap;
import java.util.Map;
import spark.Request;
import spark.Response;
import spark.Route;
import static spark.Spark.get;

public class WebApp {

    private static Map<String, Route> routes = new HashMap<>();

    public static void main(String[] args) {
        get("/hello/:username", escapeDecorator(hello()));
    }

    private static Route hello() {
        return (Request request, Response response) -> {
            String username = request.params(":username");
            return "Hello " + escape(username);
        };
    }

    private static Route escapeDecorator(Route route) {
        return (Request request, Response response) -> {
            String result = route.handle(request, response).toString();
            return escape(result);
        };
    }

    private static String escape(String input) {
        return input
                .replace("&", "&amp;")
                .replace("<", "&lt;")
                .replace(">", "&gt;")
                .replace("\"", "&quot;")
                .replace("'", "&#039;");
    }
}