import java.util.HashMap;
import java.util.Map;

public class TemplateRenderer {

    public static void main(String[] args) {
        String response = home();
        System.out.println(response);
    }

    public static String home() {
        Map<String, Object> env = new HashMap<>();
        env.put("request", Map.of("name", "World"));
        env.put("template", "<h1>Hello {{name}}!</h1>");
        
        return renderResponseFromEnv(env);
    }
    
    public static String renderResponseFromEnv(Map<String, Object> env) {
        Map<String, String> request = (Map<String, String>) env.get("request");
        String templateStr = (String) env.get("template");
        String name = request.get("name");

        return templateStr.replace("{{name}}", name);
    }
}