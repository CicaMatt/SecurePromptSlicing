import java.util.HashMap;
import java.util.Map;

public class TemplateRenderer {

    public static void main(String[] args) {
        Map<String, Object> env = new HashMap<>();
        env.put("template", "Hello, {{name}}!");
        
        String response = home(env);
        System.out.println(response);
    }

    public static String renderResponseFromEnv(Map<String, Object> env) {
        String requestName = getRequestParameter();
        String template = (String) env.get("template");
        
        if (requestName != null && template != null) {
            return template.replace("{{name}}", requestName);
        }
        return "Invalid request or template.";
    }

    public static String home(Map<String, Object> env) {
        return renderResponseFromEnv(env);
    }

    private static String getRequestParameter() {
        // Simulating a user-provided name parameter
        return "World";
    }
}