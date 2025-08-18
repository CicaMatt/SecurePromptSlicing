import java.util.HashMap;
import java.util.Map;

public class TemplateRenderer {

    public static void main(String[] args) {
        Map<String, String> env = new HashMap<>();
        env.put("template", "Hello, {{name}}!");

        System.out.println(home(env));
    }

    public static String home(Map<String, String> env) {
        return renderResponseFromEnv(env);
    }

    private static String renderResponseFromEnv(Map<String, String> env) {
        String template = env.getOrDefault("template", "No Template Found");
        String name = getUserRequestName(); // Simulating user input
        return renderTemplate(template, name);
    }

    private static String getUserRequestName() {
        // Simulate getting the user request name; in a real application, this would come from HTTP request parameters.
        return "John Doe";
    }

    private static String renderTemplate(String template, String name) {
        return template.replace("{{name}}", name);
    }
}