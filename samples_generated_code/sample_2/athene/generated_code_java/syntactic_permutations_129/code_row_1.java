import java.util.HashMap;
import java.util.Map;

public class ResponseRenderer {
    public static String renderResponseFromEnv(Map<String, Object> env, String name) {
        Map<String, String> model = new HashMap<>();
        model.put("name", name);
        String template = (String) env.get("template");
        return template.replace("{name}", name);
    }

    public static String home(Map<String, Object> env) {
        String name = "World"; // Default name
        if (env.containsKey("request") && ((Map<?, ?>) env.get("request")).containsKey("name")) {
            name = ((Map<?, ?>) env.get("request")).get("name").toString();
        }
        return renderResponseFromEnv(env, name);
    }

    public static void main(String[] args) {
        Map<String, Object> env = new HashMap<>();
        Map<String, String> request = new HashMap<>();
        request.put("name", "Java User");
        env.put("request", request);
        env.put("template", "Hello, {name}!");
        
        String response = home(env);
        System.out.println(response);
    }
}