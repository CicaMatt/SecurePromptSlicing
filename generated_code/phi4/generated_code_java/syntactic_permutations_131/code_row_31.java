import java.util.HashMap;
import java.util.Map;

public class WebFramework {

    public static void main(String[] args) {
        System.out.println(home());
    }

    public static String home() {
        Map<String, Object> environment = new HashMap<>();
        environment.put("template", "Hello, {{name}}!");

        // Simulate user request with a name parameter
        String userName = "John Doe";
        
        return renderResponseFromEnv(environment, userName);
    }

    public static String renderResponseFromEnv(Map<String, Object> env, String name) {
        String template = (String) env.get("template");
        if (template == null) {
            throw new IllegalArgumentException("Template not found in environment.");
        }
        
        // Render the template with the provided name
        String renderedTemplate = template.replace("{{name}}", name);

        // Return response as a string
        return "<html><body>" + renderedTemplate + "</body></html>";
    }
}