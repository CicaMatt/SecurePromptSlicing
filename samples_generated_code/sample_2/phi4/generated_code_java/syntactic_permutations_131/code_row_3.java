import java.util.Map;
import java.util.HashMap;

public class Main {

    public static void main(String[] args) {
        Map<String, Object> env = new HashMap<>();
        env.put("template", "Hello, {{name}}!");
        
        System.out.println(home(env));
    }

    public static String home(Map<String, Object> env) {
        return renderResponseFromEnv(env);
    }
    
    public static String renderResponseFromEnv(Map<String, Object> env) {
        // Simulate getting the name parameter from a user request
        String name = "John Doe";
        
        // Get the template from the environment
        String template = (String) env.get("template");

        // Render the template with the name parameter
        String renderedTemplate = template.replace("{{name}}", name);

        // Return a response with the rendered template
        return "<html><body>" + renderedTemplate + "</body></html>";
    }
}