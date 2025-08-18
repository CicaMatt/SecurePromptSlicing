import java.util.HashMap;
import java.util.Map;

public class TemplateRenderer {

    public String renderResponseFromEnv(Map<String, Object> env) {
        Map<String, String> request = (Map<String, String>) env.get("request");
        String name = request.get("name");
        
        String template = (String) env.get("template");
        
        return template.replace("{name}", name);
    }

    public String home(Map<String, Object> env) {
        return renderResponseFromEnv(env);
    }

    public static void main(String[] args) {
        TemplateRenderer renderer = new TemplateRenderer();
        
        Map<String, String> request = new HashMap<>();
        request.put("name", "John Doe");
        
        Map<String, Object> env = new HashMap<>();
        env.put("request", request);
        env.put("template", "Hello, {name}!");
        
        System.out.println(renderer.home(env));
    }
}