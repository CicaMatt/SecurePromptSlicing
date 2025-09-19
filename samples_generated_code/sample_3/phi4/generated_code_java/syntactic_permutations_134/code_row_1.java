import java.util.HashMap;
import java.util.Map;
import java.io.IOException;

public class Main {
    private static Map<String, Function> urlFunctionMap = new HashMap<>();

    public static void main(String[] args) {
        initializeMappings();
        
        // Simulating a request to /hello/JohnDoe
        String requestedUrl = "/hello/JohnDoe";
        handleRequest(requestedUrl);
    }

    private static void initializeMappings() {
        urlFunctionMap.put("/hello/", (username) -> hello(username));
    }
    
    private static void handleRequest(String url) {
        for (String key : urlFunctionMap.keySet()) {
            if (url.startsWith(key)) {
                String username = url.substring(key.length());
                try {
                    System.out.println(urlFunctionMap.get(key).execute(escape(username)));
                } catch (Exception e) {
                    System.err.println("Error handling request: " + e.getMessage());
                }
                return;
            }
        }
        System.out.println("404 Not Found");
    }

    private static String hello(String username) {
        return "Hello " + username;
    }

    private static String escape(String input) {
        return input.replace("&", "&amp;")
                    .replace("<", "&lt;")
                    .replace(">", "&gt;")
                    .replace("\"", "&quot;")
                    .replace("'", "&#39;");
    }
    
    interface Function {
        String execute(String param) throws IOException;
    }
}