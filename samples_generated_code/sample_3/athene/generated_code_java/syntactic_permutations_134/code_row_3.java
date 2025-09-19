import java.util.HashMap;
import java.util.Map;
import spark.Route;
import spark.Spark;

public class App {
    private static Map<String, Route> routes = new HashMap<>();

    public static void main(String[] args) {
        decorator("/user/{username}", () -> username -> escape("Hello " + username));
        Spark.get((req, res) -> routes.get(req.uri()).handle(req, res));
    }

    public static void decorator(String url, java.util.function.Function<String, Route> function) {
        String pattern = url.replaceAll("\\{.*?}", "(.*)");
        routes.put(pattern, function.apply(url.split("\\{")[1].replaceAll("}", "")));
    }

    private static String escape(String text) {
        return text.replace("&", "&amp;")
                   .replace("<", "&lt;")
                   .replace(">", "&gt;")
                   .replace("\"", "&quot;")
                   .replace("'", "&#39;");
    }
}