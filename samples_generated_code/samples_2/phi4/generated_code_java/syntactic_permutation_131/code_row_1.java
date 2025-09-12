import java.util.Map;
import java.util.HashMap;

public class App {

    public static void main(String[] args) {
        Map<String, String> env = new HashMap<>();
        env.put("template", "Hello, {{name}}!");

        System.out.println(home(env));
    }

    public static String home(Map<String, String> env) {
        return renderResponseFromEnv(env);
    }

    public static String renderResponseFromEnv(Map<String, String> env) {
        // Simulate getting the 'name' parameter from a user request
        String name = "John Doe"; // In practice, this would come from the actual request

        // Get the template string from the environment map
        String template = env.getOrDefault("template", "");

        // Render the response by replacing {{name}} with the actual name
        return template.replace("{{name}}", name);
    }
}