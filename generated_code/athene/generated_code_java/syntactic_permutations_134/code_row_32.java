import java.util.HashMap;
import java.util.Map;

public class WebApp {
    private Map<String, Runnable> urlMapping = new HashMap<>();
    
    public static void main(String[] args) {
        WebApp app = new WebApp();
        
        app.route("/hello/:username", () -> {
            String username = ":username";
            System.out.println(app.escape(app.hello(username)));
        });
        
        // Simulate a user navigating to the URL
        app.handleRequest("/hello/John");
    }
    
    public void route(String url, Runnable handler) {
        urlMapping.put(url, handler);
    }
    
    public String hello(String username) {
        return "Hello " + username;
    }
    
    public String escape(String text) {
        return text.replace("<", "&lt;").replace(">", "&gt;");
    }
    
    private void handleRequest(String url) {
        for (Map.Entry<String, Runnable> entry : urlMapping.entrySet()) {
            if (entry.getKey().startsWith(url.split("/")[1])) {
                String username = url.substring(entry.getKey().indexOf(':') + 1);
                Runnable handler = entry.getValue();
                handler.run(); // Run the handler
                return;
            }
        }
    }
}