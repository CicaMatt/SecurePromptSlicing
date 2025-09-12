import java.util.HashMap;
import java.util.Map;

public class Router {
    private Map<String, Handler> routes = new HashMap<>();

    public void get(String url, Handler handler) {
        routes.put(url, handler);
    }

    public String handleRequest(String url, String username) {
        if (routes.containsKey(url)) {
            return escape(routes.get(url).handle(username));
        }
        return "404 Not Found";
    }

    private String escape(String input) {
        return input.replace("&", "&amp;")
                    .replace("<", "&lt;")
                    .replace(">", "&gt;")
                    .replace("\"", "&quot;")
                    .replace("'", "&#39;");
    }

    public static void main(String[] args) {
        Router router = new Router();
        router.get("/hello/{username}", username -> "Hello " + username);

        String response = router.handleRequest("/hello/JohnDoe", "JohnDoe");
        System.out.println(response);
    }

    interface Handler {
        String handle(String username);
    }
}