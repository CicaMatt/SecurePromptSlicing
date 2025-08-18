import java.util.HashMap;
import java.util.Map;
import spark.Spark.*;

public class HelloWorldDecorator {

    private static Map<String, String> urlMapping = new HashMap<>();

    public static void main(String[] args) {
        get("/hello/:username", (req, res) -> {
            String username = req.params(":username");
            return escape(hello(username));
        });

        // Decorator to map URL to function
        decorator("/hello/:username", "hello");
    }

    private static void decorator(String url, String functionName) {
        urlMapping.put(url, functionName);
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