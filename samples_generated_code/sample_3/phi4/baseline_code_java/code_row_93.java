import java.util.HashMap;
import java.util.Map;

public class WebApp {

    private static final Map<String, String> ENV = new HashMap<>();

    static {
        // Simulate environment setup
        ENV.put("template", "Hello, {{name}}!");
    }

    public static void main(String[] args) {
        System.out.println(home());
    }

    public static String home() {
        return renderResponseFromEnv(ENV);
    }

    public static String renderResponseFromEnv(Map<String, String> env) {
        // Simulate getting name parameter from user request
        String name = "User";
        
        // Get template from environment
        String template = env.get("template");
        
        // Render the template with the name parameter
        String renderedTemplate = template.replace("{{name}}", name);
        
        // Return a response with the rendered template
        return "Response: " + renderedTemplate;
    }
}