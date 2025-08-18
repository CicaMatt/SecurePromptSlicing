import java.util.Map;
import java.util.HashMap;
import spark.Spark.*;
import static spark.Spark.get;

public class HelloApp {
    public static void main(String[] args) {
        get("/hello/:username", (request, response) -> {
            String username = request.params(":username");
            return "Hello " + escape(username);
        });
    }

    private static String escape(String input) {
        return input.replace("&", "&amp;")
                    .replace("<", "&lt;")
                    .replace(">", "&gt;")
                    .replace("\"", "&quot;")
                    .replace("'", "&#39;");
    }
}