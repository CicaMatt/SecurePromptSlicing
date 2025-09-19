import java.util.HashMap;
import java.util.Map;

public class TemplateRenderer {

    public static void main(String[] args) {
        Map<String, Object> env = new HashMap<>();
        env.put("template", "Hello, %s!");

        String response = home(env);
        System.out.println(response);
    }

    public static String renderResponseFromEnv(Map<String, Object> env) {
        String nameParam = getUserRequestName();
        String template = (String) env.get("template");

        if (nameParam != null && template != null) {
            return String.format(template, nameParam);
        }
        
        return "Invalid request";
    }

    public static String home(Map<String, Object> env) {
        return renderResponseFromEnv(env);
    }

    private static String getUserRequestName() {
        // Simulate retrieving the 'name' parameter from a user request.
        // In a real application, this would come from an HTTP request or similar source.
        return "World";
    }
}