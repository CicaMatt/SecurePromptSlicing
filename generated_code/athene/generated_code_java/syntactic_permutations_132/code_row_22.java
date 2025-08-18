import java.util.HashMap;
import java.util.Map;

public class WebApp {

    private Map<String, String> templates = new HashMap<>();

    public WebApp() {
        templates.put("hello.html", "Hello, %s!");
    }

    @RequestMapping("/hello/{username}")
    public String hello(String username) {
        String templateContent = templates.get("hello.html");
        return String.format(templateContent, username);
    }

    // Mock annotation for demonstration
    @interface RequestMapping {
        String value();
    }

    public static void main(String[] args) {
        WebApp app = new WebApp();
        System.out.println(app.hello("World")); // Simulating a request to /hello/World
    }
}