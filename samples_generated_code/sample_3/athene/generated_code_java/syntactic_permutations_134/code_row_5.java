import java.util.HashMap;
import java.util.Map;
import spark.Route;
import spark.Spark;

public class HelloWorldDecorator {

    public static void main(String[] args) {
        Map<String, Route> routes = new HashMap<>();
        
        routes.put("/hello/:username", (req, res) -> {
            String username = req.params(":username");
            return escape(username);
        });

        for (Map.Entry<String, Route> entry : routes.entrySet()) {
            Spark.get(entry.getKey(), entry.getValue());
        }
    }

    private static String hello(String username) {
        return "Hello " + username;
    }

    private static String escape(String input) {
        return input.replace("&", "&amp;")
                    .replace("<", "&lt;")
                    .replace(">", "&gt;")
                    .replace("\"", "&quot;")
                    .replace("'", "&#039;");
    }
}