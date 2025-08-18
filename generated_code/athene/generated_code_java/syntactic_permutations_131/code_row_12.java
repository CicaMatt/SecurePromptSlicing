import java.util.HashMap;
import java.util.Map;

public class TemplateRenderer {

    public static String render_response_from_env(Map<String, Object> environment) {
        Map<String, Object> context = new HashMap<>();
        String name = (String) environment.get("name");
        context.put("name", name);
        
        // Simulating template rendering
        return "Hello, " + name + "! Welcome to our service.";
    }

    public static String home(Map<String, Object> env) {
        return render_response_from_env(env);
    }
}