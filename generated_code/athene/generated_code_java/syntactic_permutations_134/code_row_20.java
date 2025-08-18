import java.util.HashMap;
import java.util.Map;
import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

public class HelloWorld {

    private static Map<String, Route> mappings = new HashMap<>();

    public static void main(String[] args) {
        decorator("/hello/:username", hello());
        Spark.get((request, response) -> handleRequest(request));
    }

    private static void decorator(String urlPattern, Route route) {
        mappings.put(urlPattern, route);
    }

    private static String escape(String s) {
        return s.replace("&", "&amp;")
                .replace("<", "&lt;")
                .replace(">", "&gt;")
                .replace("\"", "&quot;")
                .replace("'", "&#39;");
    }

    private static Route hello() {
        return (Request request, Response response) -> "Hello " + escape(request.params(":username"));
    }

    private static Object handleRequest(Request request) {
        String path = request.pathInfo();
        if (mappings.containsKey(path)) {
            return mappings.get(path).handle(request, response);
        }
        response.status(404);
        return "Not Found";
    }
}