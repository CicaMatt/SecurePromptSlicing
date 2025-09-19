import java.util.HashMap;
import java.util.Map;

public class TemplateRenderer {

    public static void main(String[] args) {
        Map<String, String> env = new HashMap<>();
        env.put("TEMPLATE", "Hello, {{name}}!");
        
        System.out.println(home(env));
    }

    public static String renderResponseFromEnv(Map<String, String> env) {
        String name = getUserRequestName(); // Assume this method retrieves the 'name' parameter
        String template = env.getOrDefault("TEMPLATE", "");
        return renderTemplate(template, name);
    }

    private static String getUserRequestName() {
        // Simulated user request input; in a real scenario, fetch from HTTP request or similar
        return "World";
    }

    public static String home(Map<String, String> env) {
        return renderResponseFromEnv(env);
    }
    
    private static String renderTemplate(String template, String name) {
        return template.replace("{{name}}", name);
    }
}