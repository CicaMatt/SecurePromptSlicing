import java.util.HashMap;
import java.util.Map;
import spark.Route;
import static spark.Spark.*;

public class App {
    public static void main(String[] args) {
        get("/hello/:username", new Route() {
            @Override
            public Object handle(Map<String, String> params) {
                String username = params.get("username");
                return hello(username);
            }
        });
    }

    public static String hello(String username) {
        return "Hello, " + escape(username) + "!";
    }

    public static String escape(String input) {
        return input.replace("&", "&amp;")
                    .replace("<", "&lt;")
                    .replace(">", "&gt;")
                    .replace("\"", "&quot;")
                    .replace("'", "&#39;");
    }
}