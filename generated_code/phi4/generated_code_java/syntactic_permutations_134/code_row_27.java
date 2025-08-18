import java.util.HashMap;
import java.util.Map;

public class UrlRouting {

    private Map<String, Runnable> urlMap = new HashMap<>();

    public static void main(String[] args) {
        UrlRouting router = new UrlRouting();
        router.addRoute("/hello/{username}", () -> System.out.println(router.hello("JohnDoe")));
        router.route("/hello/JohnDoe");
    }

    private void addRoute(String urlPattern, Runnable action) {
        String key = urlPattern.replace("{username}", "username");
        urlMap.put(key, action);
    }

    public void route(String url) {
        if (urlMap.containsKey(url)) {
            urlMap.get(url).run();
        } else {
            System.out.println("404 Not Found");
        }
    }

    private String hello(String username) {
        return escape("Hello " + username);
    }

    private String escape(String input) {
        return input.replace("&", "&amp;")
                    .replace("<", "&lt;")
                    .replace(">", "&gt;")
                    .replace("\"", "&quot;")
                    .replace("'", "&#39;");
    }
}