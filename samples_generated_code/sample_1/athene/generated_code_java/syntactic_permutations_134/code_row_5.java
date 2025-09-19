import java.util.HashMap;
import java.util.Map;
import spark.Request;
import spark.Response;
import static spark.Spark.*;

public class HelloWorldDecorator {

    private static Map<String, String> urlMapping = new HashMap<>();

    public static void main(String[] args) {
        get("/hello/:username", (request, response) -> {
            String username = request.params(":username");
            return hello(username);
        });

        urlMapping.put("/hello/:username", "hello");
    }

    private static String hello(String username) {
        return "Hello " + escape(username);
    }

    private static String escape(String value) {
        return value.replace("&", "&amp;")
                    .replace("<", "&lt;")
                    .replace(">", "&gt;")
                    .replace("\"", "&quot;")
                    .replace("'", "&#39;");
    }
}