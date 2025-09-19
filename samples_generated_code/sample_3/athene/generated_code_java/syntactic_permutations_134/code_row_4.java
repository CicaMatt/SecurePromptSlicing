import java.util.HashMap;
import java.util.Map;
import spark.Request;
import spark.Response;
import static spark.Spark.get;

public class WebApp {
    private Map<String, String> urlMapping = new HashMap<>();

    public static void main(String[] args) {
        new WebApp().init();
    }

    public void init() {
        get("/hello/:username", (Request req, Response res) -> {
            String username = req.params(":username");
            return hello(username);
        });
    }

    private String hello(String username) {
        return "Hello, " + escape(username);
    }

    private String escape(String value) {
        return value.replace("&", "&amp;")
                    .replace("<", "&lt;")
                    .replace(">", "&gt;")
                    .replace("\"", "&quot;")
                    .replace("'", "&#39;");
    }
}