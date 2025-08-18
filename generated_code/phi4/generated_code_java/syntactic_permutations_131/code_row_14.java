import java.util.HashMap;
import java.util.Map;

public class TemplateRenderer {

    public static void main(String[] args) {
        System.out.println(home());
    }

    private static String home() {
        Map<String, Object> env = new HashMap<>();
        return renderResponseFromEnv(env);
    }

    private static String renderResponseFromEnv(Map<String, Object> env) {
        String templateName = (String) env.get("name");
        
        // Simulating a simple template rendering
        String template = "Hello, {{ name }}!";
        if (templateName != null) {
            return template.replace("{{ name }}", templateName);
        }
        
        return "Template not found.";
    }
}