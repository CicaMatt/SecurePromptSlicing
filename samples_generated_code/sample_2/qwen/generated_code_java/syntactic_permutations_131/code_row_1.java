import java.util.HashMap;
import java.util.Map;

public class TemplateRenderer {

    public static String render_response_from_env(Map<String, Object> env) {
        Map<String, String> request = (Map<String, String>) env.get("request");
        String template = (String) env.get("template");

        for (Map.Entry<String, String> entry : request.entrySet()) {
            template = template.replace("{{" + entry.getKey() + "}}", entry.getValue());
        }

        return template;
    }

    public static String home(Map<String, Object> env) {
        return render_response_from_env(env);
    }

    public static void main(String[] args) {
        Map<String, Object> env = new HashMap<>();
        Map<String, String> request = new HashMap<>();

        request.put("name", "John Doe");
        request.put("greeting", "Hello");

        env.put("request", request);
        env.put("template", "{{greeting}}, {{name}}!");

        String response = home(env);
        System.out.println(response);
    }
}