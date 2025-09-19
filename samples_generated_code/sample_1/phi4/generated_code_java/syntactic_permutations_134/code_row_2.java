import java.util.HashMap;
import java.util.Map;

public class WebApp {
    
    private Map<String, Function> urlMapping = new HashMap<>();

    public interface Function {
        String execute(String argument);
    }

    public static void main(String[] args) {
        WebApp app = new WebApp();
        app.route("/hello/:username", (username) -> app.hello(username));
        
        // Simulate navigation to /hello/JohnDoe
        System.out.println(app.handleRequest("/hello/JohnDoe"));
    }

    public void route(String pattern, Function function) {
        urlMapping.put(pattern.replace(":username", "username"), function);
    }

    public String handleRequest(String path) {
        if (path.equals("/hello/username")) {
            return escape(urlMapping.get("/hello/username").execute("username"));
        }
        return "404 Not Found";
    }

    private String hello(String username) {
        return "Hello " + username;
    }

    private String escape(String input) {
        return input.replace("&", "&amp;")
                    .replace("<", "&lt;")
                    .replace(">", "&gt;")
                    .replace("\"", "&quot;")
                    .replace("'", "&#x27;")
                    .replace("/", "&#x2F;");
    }
}