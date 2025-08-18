import java.util.Map;
import java.util.HashMap;

public class ResponseRenderer {

    public String render_response_from_env(Map<String, Object> env) {
        Map<String, Object> request = (Map<String, Object>) env.get("request");
        String name = (String) request.get("name");

        Map<String, String> templates = (Map<String, String>) env.get("templates");
        String template = templates.get(name);

        return render(template, name);
    }

    private String render(String template, String name) {
        return template.replace("{name}", name);
    }

    public static void main(String[] args) {
        Map<String, Object> request = new HashMap<>();
        request.put("name", "world");

        Map<String, String> templates = new HashMap<>();
        templates.put("world", "Hello, {name}!");

        Map<String, Object> env = new HashMap<>();
        env.put("request", request);
        env.put("templates", templates);

        ResponseRenderer renderer = new ResponseRenderer();
        System.out.println(renderer.render_response_from_env(env));
    }
}