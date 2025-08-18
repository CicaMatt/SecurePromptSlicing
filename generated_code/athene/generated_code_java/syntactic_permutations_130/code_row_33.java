import java.util.HashMap;
import java.util.Map;

public class ResponseRenderer {

    public static String render_response_from_env(Map<String, Object> env) {
        Map<String, Object> request = (Map<String, Object>) env.get("request");
        String name = (String) request.get("name");
        
        String template = (String) env.get("template");
        String renderedTemplate = template.replace("{name}", name);
        
        return renderedTemplate;
    }

    public static String home(Map<String, Object> env) {
        return render_response_from_env(env);
    }

    public static void main(String[] args) {
        Map<String, Object> request = new HashMap<>();
        request.put("name", "World");

        Map<String, Object> env = new HashMap<>();
        env.put("request", request);
        env.put("template", "Hello, {name}!");

        String response = home(env);
        System.out.println(response);
    }
}