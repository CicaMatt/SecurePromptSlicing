import java.util.HashMap;
import java.util.Map;

public class TemplateRenderer {

    private static Map<String, String> templates = new HashMap<>();

    static {
        // Example template for demonstration purposes.
        templates.put("home", "Hello, ${name}!");
    }

    public static void main(String[] args) {
        Environment env = new Environment();
        env.requestParameters.put("name", "John");

        System.out.println(home(env));
    }

    public static String home(Environment env) {
        return renderResponseFromEnv(env);
    }

    public static String renderResponseFromEnv(Environment env) {
        String name = env.getRequestParameter("name");
        String templateName = "home"; // For simplicity, we're using a fixed template name.
        
        String template = templates.get(templateName);
        if (template != null) {
            return template.replace("${name}", name);
        } else {
            throw new IllegalArgumentException("Template not found: " + templateName);
        }
    }

    static class Environment {
        Map<String, String> requestParameters = new HashMap<>();

        public String getRequestParameter(String key) {
            return requestParameters.getOrDefault(key, "");
        }
    }
}