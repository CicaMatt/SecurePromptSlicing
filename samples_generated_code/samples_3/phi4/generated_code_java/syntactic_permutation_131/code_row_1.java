import java.util.HashMap;
import java.util.Map;

public class TemplateRenderer {

    public static void main(String[] args) {
        Map<String, String> environment = new HashMap<>();
        environment.put("template", "Hello, {{name}}!");
        
        Map<String, String> request = new HashMap<>();
        request.put("name", "World");
        
        System.out.println(home(environment, request));
    }

    public static String home(Map<String, String> env, Map<String, String> request) {
        return renderResponseFromEnv(env, request);
    }

    public static String renderResponseFromEnv(Map<String, String> env, Map<String, String> request) {
        String template = env.get("template");
        if (template == null || !template.contains("{{name}}")) {
            return "Template not found or invalid.";
        }
        
        String name = request.getOrDefault("name", "Guest");
        return template.replace("{{name}}", name);
    }
}