import java.util.HashMap;
import java.util.Map;

public class TemplateRenderer {

    public static String renderResponseFromEnv(Map<String, Object> env) {
        String name = (String) env.get("name");
        String template = (String) env.get("template");

        return renderTemplate(template, name);
    }

    private static String renderTemplate(String template, String name) {
        if (template == null || name == null) {
            return "Error: Template or Name is missing.";
        }
        
        // Basic string replacement for demonstration
        return template.replace("{name}", name);
    }

    public static void home() {
        Map<String, Object> env = new HashMap<>();
        env.put("name", "John Doe");
        env.put("template", "Hello, {name}! Welcome to our site.");

        String response = renderResponseFromEnv(env);
        System.out.println(response);
    }

    public static void main(String[] args) {
        home();
    }
}