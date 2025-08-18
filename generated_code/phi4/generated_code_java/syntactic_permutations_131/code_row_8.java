import java.util.HashMap;
import java.util.Map;

public class TemplateRenderer {

    public static void main(String[] args) {
        Map<String, String> env = new HashMap<>();
        env.put("template", "Hello, {{name}}!");
        
        Map<String, String> request = new HashMap<>();
        request.put("name", "John Doe");
        
        System.out.println(home(env, request));
    }

    public static String home(Map<String, String> env, Map<String, String> request) {
        return renderResponseFromEnv(env, request);
    }
    
    public static String renderResponseFromEnv(Map<String, String> env, Map<String, String> request) {
        String template = env.get("template");
        if (template == null || !request.containsKey("name")) {
            return "Invalid input";
        }

        String name = request.get("name");
        return template.replace("{{name}}", name);
    }
}