import java.util.HashMap;
import java.util.Map;

public class TemplateRenderer {

    public static void main(String[] args) {
        Map<String, String> env = new HashMap<>();
        env.put("REQUEST_METHOD", "GET");
        env.put("PATH_INFO", "/");
        
        System.out.println(home(env));
    }

    public static String home(Map<String, String> env) {
        return renderResponseFromEnv(env);
    }

    public static String renderResponseFromEnv(Map<String, String> env) {
        String name = getRequestParam(env, "name");
        String template = getTemplateFromEnv(env);
        
        if (template == null || name == null) {
            return "Name or Template not provided.";
        }
        
        return renderTemplate(template, name);
    }

    private static String getRequestParam(Map<String, String> env, String param) {
        // Simulate fetching request parameters
        // In a real-world scenario, this would be extracted from the HTTP request object
        if ("name".equals(param)) {
            return "John Doe";  // Example static value for demonstration purposes
        }
        return null;
    }

    private static String getTemplateFromEnv(Map<String, String> env) {
        // Simulate fetching a template string from environment
        // This would usually be loaded from a file or external resource in real-world applications
        return "Hello, %s! Welcome to our application.";
    }

    private static String renderTemplate(String template, String name) {
        if (template != null && name != null) {
            return String.format(template, name);
        }
        return "";
    }
}