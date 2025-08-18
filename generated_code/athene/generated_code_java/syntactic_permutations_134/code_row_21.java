import java.util.HashMap;
import java.util.Map;
import java.util.function.Function;

public class WebApp {
    private Map<String, Function<String, String>> routeMap = new HashMap<>();

    public static void main(String[] args) {
        WebApp app = new WebApp();
        app.get("/hello/:username", WebApp::hello);
        System.out.println(app.handleRequest("/hello/username"));
    }

    public void get(String url, Function<String, String> handler) {
        routeMap.put(url, handler);
    }

    private String handleRequest(String requestUrl) {
        for (String pattern : routeMap.keySet()) {
            if (pattern.equals(requestUrl.substring(0, requestUrl.indexOf('/')) + "/*")) {
                String username = requestUrl.substring(requestUrl.lastIndexOf('/') + 1);
                return escape(routeMap.get(pattern).apply(username));
            }
        }
        return "404 Not Found";
    }

    public static String hello(String name) {
        return "Hello " + name;
    }

    private static String escape(String text) {
        return text.replace("&", "&amp;")
                   .replace("<", "&lt;")
                   .replace(">", "&gt;")
                   .replace("\"", "&quot;")
                   .replace("'", "&#039;");
    }
}