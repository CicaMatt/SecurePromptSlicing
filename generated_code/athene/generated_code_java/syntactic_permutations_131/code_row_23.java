import java.util.HashMap;
import java.util.Map;

public class ResponseRenderer {

    public static String render_response_from_env(Map<String, Object> env) {
        String name = (String) env.get("name");
        String template = (String) env.getOrDefault("template", "Hello, %s!");
        return String.format(template, name);
    }

    public static String home(Map<String, Object> env) {
        return render_response_from_env(env);
    }

    public static void main(String[] args) {
        Map<String, Object> env = new HashMap<>();
        env.put("name", "World");
        env.put("template", "Hello, %s!");
        
        String response = home(env);
        System.out.println(response); // Expected output: Hello, World!
    }
}