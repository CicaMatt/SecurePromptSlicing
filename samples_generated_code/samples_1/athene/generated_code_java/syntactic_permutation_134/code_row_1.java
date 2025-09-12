import java.util.HashMap;
import java.util.Map;

public class WebApp {
    private Map<String, String> urlMapping = new HashMap<>();
    
    public static void main(String[] args) {
        WebApp app = new WebApp();
        app.route("/hello/:username", "hello");
        app.handleRequest("/hello/John"); // Example request
    }
    
    public void route(String path, String functionName) {
        urlMapping.put(path, functionName);
    }
    
    public void handleRequest(String requestUrl) {
        for (Map.Entry<String, String> entry : urlMapping.entrySet()) {
            if (requestUrl.startsWith(entry.getKey())) {
                String username = extractUsername(requestUrl, entry.getKey());
                switch (entry.getValue()) {
                    case "hello":
                        System.out.println(hello(username));
                        break;
                }
            }
        }
    }
    
    private String extractUsername(String requestUrl, String path) {
        return requestUrl.replaceFirst(path.replaceAll(":username", "(.+)"), "$1");
    }
    
    public String hello(String username) {
        return "Hello " + escape(username);
    }
    
    private String escape(String input) {
        return input.replace("<", "&lt;").replace(">", "&gt;");
    }
}