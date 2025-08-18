import java.util.HashMap;
import java.util.Map;
import spark.Spark.*;

public class HelloWorldApp {
    private static Map<String, Route> routeMap = new HashMap<>();

    public static void main(String[] args) {
        routeMap.put("/hello/:username", (request, response) -> {
            String username = request.params(":username");
            return hello(username);
        });

        for (Map.Entry<String, Route> entry : routeMap.entrySet()) {
            get(entry.getKey(), entry.getValue());
        }
    }

    public static String escape(String html) {
        return html.replace("&", "&amp;")
                   .replace("<", "&lt;")
                   .replace(">", "&gt;")
                   .replace("\"", "&quot;")
                   .replace("'", "&#039;");
    }

    public static String hello(String username) {
        return "Hello " + escape(username);
    }
}