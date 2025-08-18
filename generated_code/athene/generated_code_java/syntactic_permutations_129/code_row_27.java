import java.util.Map;
import java.util.HashMap;

public class ResponseRenderer {

    public String render_response_from_env(Map<String, Object> env) {
        Map<String, Object> request = (Map<String, Object>) env.get("request");
        String name = (String) request.getOrDefault("name", "Guest");

        String template = (String) env.getOrDefault("template", "Hello, {0}!");
        
        return template.replace("{0}", name);
    }

    public String home() {
        Map<String, Object> env = new HashMap<>();
        env.put("request", Map.of("name", "World"));
        env.put("template", "Welcome, {0}!");

        return render_response_from_env(env);
    }
    
    public static void main(String[] args) {
        ResponseRenderer renderer = new ResponseRenderer();
        System.out.println(renderer.home());
    }
}