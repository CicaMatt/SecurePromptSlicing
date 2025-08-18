import java.util.HashMap;
import java.util.Map;

public class TemplateRenderer {

    public static void main(String[] args) {
        System.out.println(home());
    }

    public static String home() {
        Map<String, String> env = new HashMap<>();
        env.put("template", "Hello, {{name}}!");

        return renderResponseFromEnv(env);
    }

    public static String renderResponseFromEnv(Map<String, String> environment) {
        // Simulate getting the name parameter from a user request
        String nameParam = "World";

        // Get the template from the environment
        String template = environment.get("template");

        // Render the template with the name parameter
        String renderedTemplate = template.replace("{{name}}", nameParam);

        // Return the response with the rendered template
        return renderedTemplate;
    }
}