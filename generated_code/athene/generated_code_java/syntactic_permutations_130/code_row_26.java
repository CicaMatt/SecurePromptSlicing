import java.util.Map;
import java.util.HashMap;

public class Renderer {
    public static void main(String[] args) {
        Map<String, Object> env = new HashMap<>();
        env.put("template", "Hello, {{name}}!");
        Map<String, String> request = new HashMap<>();
        request.put("name", "World");
        env.put("request", request);

        System.out.println(home(env));
    }

    public static String render_response_from_env(Map<String, Object> env) {
        Map<String, String> request = (Map<String, String>) env.get("request");
        String name = request.get("name");
        String template = (String) env.get("template");

        return template.replace("{{name}}", name);
    }

    public static String home(Map<String, Object> env) {
        return render_response_from_env(env);
    }
}