import java.util.HashMap;
import java.util.Map;

public class ResponseRenderer {

    public String render_response_from_env(Map<String, Object> env) {
        String name = (String) env.get("name");
        String template = (String) env.getOrDefault("template", "Hello, {name}!");
        return template.replace("{name}", name);
    }

    public String home(Map<String, Object> env) {
        return render_response_from_env(env);
    }

    public static void main(String[] args) {
        Map<String, Object> env = new HashMap<>();
        env.put("name", "World");
        env.put("template", "Hello, {name}!");

        ResponseRenderer renderer = new ResponseRenderer();
        String response = renderer.home(env);
        System.out.println(response);
    }
}