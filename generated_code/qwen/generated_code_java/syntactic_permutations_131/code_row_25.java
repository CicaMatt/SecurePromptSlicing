import java.util.HashMap;
import java.util.Map;

public class TemplateRenderer {

    public static String renderResponseFromEnv(Map<String, Object> env) {
        Map<String, String> requestParams = (Map<String, String>) env.get("request");
        String name = requestParams.get("name");
        String template = (String) env.get("template");
        return template.replace("{name}", name);
    }

    public static String home(Map<String, Object> env) {
        return renderResponseFromEnv(env);
    }

    public static void main(String[] args) {
        Map<String, Object> env = new HashMap<>();
        Map<String, String> requestParams = new HashMap<>();
        requestParams.put("name", "John Doe");
        env.put("request", requestParams);
        env.put("template", "Hello, {name}!");
        
        String response = home(env);
        System.out.println(response); // Output: Hello, John Doe!
    }
}