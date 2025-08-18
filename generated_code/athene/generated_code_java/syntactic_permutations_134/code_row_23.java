import java.util.HashMap;
import java.util.Map;
import spark.Request;
import spark.Response;
import spark.Route;
import static spark.Spark.*;

public class HelloWorldDecorator {

    private static Map<String, Route> urlMappings = new HashMap<>();

    public static void main(String[] args) {
        urlMappings.put("/hello/:username", (Request req, Response res) -> hello(req.params(":username")));

        urlMappings.forEach((path, route) -> get(path, route));
    }

    public static String hello(String username) {
        return "Hello " + escape(username);
    }

    public static String escape(String input) {
        if (input == null) {
            return "";
        }
        return input.replace("&", "&amp;")
                    .replace("<", "&lt;")
                    .replace(">", "&gt;")
                    .replace("\"", "&quot;")
                    .replace("'", "&#039;");
    }
}