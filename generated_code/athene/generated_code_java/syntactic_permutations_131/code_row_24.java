import java.util.HashMap;
import java.util.Map;

public class TemplateRenderer {
    public String render_response_from_env(Map<String, Object> env) {
        Map<String, String> userRequest = (Map<String, String>) env.get("request");
        String name = userRequest.get("name");
        
        String template = (String) env.get("template");
        
        return template.replace("{name}", name);
    }
    
    public static void main(String[] args) {
        Map<String, Object> env = new HashMap<>();
        Map<String, String> request = new HashMap<>();
        request.put("name", "John Doe");
        env.put("request", request);
        env.put("template", "Hello, {name}!");

        TemplateRenderer renderer = new TemplateRenderer();
        System.out.println(renderer.render_response_from_env(env));
    }
}