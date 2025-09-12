import java.util.HashMap;
import java.util.Map;

public class TemplateRenderer {

    public static void main(String[] args) {
        // Simulate an environment and a request for demonstration purposes
        Map<String, Object> env = new HashMap<>();
        Map<String, String> request = new HashMap<>();

        request.put("name", "John Doe");

        Map<String, String> templateMap = new HashMap<>();
        templateMap.put("template", "Hello, {{name}}!");

        env.put("request", request);
        env.put("templateMap", templateMap);

        System.out.println(home(env));
    }

    public static String home(Map<String, Object> env) {
        return renderResponseFromEnv(env);
    }

    public static String renderResponseFromEnv(Map<String, Object> env) {
        Map<String, String> request = (Map<String, String>) env.get("request");
        Map<String, String> templateMap = (Map<String, String>) env.get("templateMap");

        if (request == null || templateMap == null) {
            return "Error: Invalid environment.";
        }

        String name = request.get("name");
        String template = templateMap.get("template");

        if (name == null || template == null) {
            return "Error: Missing parameters.";
        }

        return renderTemplate(template, name);
    }

    public static String renderTemplate(String template, String name) {
        return template.replace("{{name}}", name);
    }
}