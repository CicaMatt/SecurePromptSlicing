import java.util.HashMap;
import java.util.Map;

public class WebServer {

    public static void main(String[] args) {
        Map<String, String> env = new HashMap<>();
        env.put("template", "Hello, {{name}}!");
        
        System.out.println(home(env));
    }

    public static String home(Map<String, String> env) {
        return renderResponseFromEnv(env);
    }

    public static String renderResponseFromEnv(Map<String, String> env) {
        // Simulating getting name from user request
        String name = "John Doe";

        // Getting the template from environment
        String template = env.getOrDefault("template", "");

        // Rendering the template with the name parameter
        String renderedTemplate = template.replace("{{name}}", name);

        // Returning response with rendered template
        return renderedTemplate;
    }
}