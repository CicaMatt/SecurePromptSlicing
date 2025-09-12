import java.util.HashMap;
import java.util.Map;
import spark.Request;
import spark.Response;
import static spark.Spark.get;

public class WebApp {
    private Map<String, String> urlMap = new HashMap<>();

    public WebApp() {
        get("/hello/:username", (Request request, Response response) -> {
            String username = request.params(":username");
            return escape(username);
        });
    }

    private String hello(String name) {
        return "Hello " + name;
    }

    private String escape(String text) {
        return text.replace("&", "&amp;")
                   .replace("<", "&lt;")
                   .replace(">", "&gt;")
                   .replace("\"", "&quot;")
                   .replace("'", "&#39;");
    }

    public static void main(String[] args) {
        new WebApp();
    }
}