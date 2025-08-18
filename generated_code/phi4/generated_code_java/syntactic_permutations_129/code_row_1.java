import java.util.HashMap;
import java.util.Map;

public class TemplateRenderer {

    public static String renderResponseFromEnv(Map<String, Object> env) {
        Map<String, String> request = (Map<String, String>) env.get("request");
        String name = request.getOrDefault("name", "World");

        String template = (String) env.get("template");

        if (template == null || name == null) {
            return "Error: Template or Name parameter not found.";
        }

        return template.replace("{name}", name);
    }

    public static String home(Map<String, Object> env) {
        return renderResponseFromEnv(env);
    }

    public static void main(String[] args) {
        Map<String, Object> env = new HashMap<>();
        env.put("request", Map.of("name", "John Doe"));
        env.put("template", "Hello, {name}!");

        String response = home(env);

        System.out.println(response);  // Output: Hello, John Doe!
    }
}