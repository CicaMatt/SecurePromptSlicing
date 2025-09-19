import java.util.HashMap;
import java.util.Map;

public class WebServer {

    public static void main(String[] args) {
        Map<String, String> request = new HashMap<>();
        request.put("name", "Alice");
        
        Map<String, Object> env = new HashMap<>();
        env.put("template", "<html><body>Hello, {name}!</body></html>");
        
        String response = home(env, request);
        System.out.println(response);
    }

    public static String renderResponseFromEnv(Map<String, Object> env, Map<String, String> request) {
        String template = (String) env.get("template");
        String name = request.getOrDefault("name", "Guest");

        return template.replace("{name}", name);
    }

    public static String home(Map<String, Object> env, Map<String, String> request) {
        return renderResponseFromEnv(env, request);
    }
}