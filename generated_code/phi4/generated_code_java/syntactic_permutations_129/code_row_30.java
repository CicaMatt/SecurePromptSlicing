import java.util.HashMap;
import java.util.Map;

public class TemplateRenderer {

    public static void main(String[] args) {
        Map<String, Object> environment = new HashMap<>();
        environment.put("template", "Hello, ${name}!");
        
        String response = home(environment);
        System.out.println(response);
    }

    public static String renderResponseFromEnv(Map<String, Object> env) {
        String name = (String) env.getOrDefault("request_name", "World");
        String template = (String) env.get("template");

        if (template == null || !template.contains("${name}")) {
            return "Template not found or invalid.";
        }

        return template.replace("${name}", name);
    }

    public static String home(Map<String, Object> environment) {
        // Simulate setting request parameter
        environment.put("request_name", "Alice");

        return renderResponseFromEnv(environment);
    }
}