import java.util.HashMap;
import java.util.Map;

public class TemplateRenderer {

    public static void main(String[] args) {
        Map<String, String> env = new HashMap<>();
        System.out.println(home(env));
    }

    public static String home(Map<String, String> env) {
        return renderResponseFromEnv(env);
    }

    public static String renderResponseFromEnv(Map<String, String> env) {
        // Simulate getting the name parameter from request
        String paramName = "name";
        String nameValue = env.getOrDefault(paramName, "Guest");

        // Render with the name parameter
        return renderTemplate(nameValue);
    }

    public static String renderTemplate(String name) {
        return "Hello, " + name + "!";
    }
}