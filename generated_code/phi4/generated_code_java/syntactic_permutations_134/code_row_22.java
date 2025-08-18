import java.util.HashMap;
import java.util.Map;

public class Main {
    public static void main(String[] args) {
        WebApp app = new WebApp();
        
        // Simulating navigation to /hello/john_doe
        String response = app.handleRequest("/hello/john_doe");
        System.out.println(response);  // Output: Hello john_doe
    }
}

class WebApp {
    private Map<String, Function> urlMap;

    public WebApp() {
        urlMap = new HashMap<>();
        urlMap.put("/hello/", this::handleHello);
    }

    public String handleRequest(String url) {
        for (String key : urlMap.keySet()) {
            if (url.startsWith(key)) {
                return urlMap.get(key).apply(url.substring(key.length()));
            }
        }
        return "404 Not Found";
    }

    private String handleHello(String username) {
        return escape("Hello ") + username;
    }

    private String escape(String text) {
        return text.replace("&", "&amp;")
                   .replace("<", "&lt;")
                   .replace(">", "&gt;")
                   .replace("\"", "&quot;")
                   .replace("'", "&#039;");
    }
}

interface Function {
    String apply(String param);
}