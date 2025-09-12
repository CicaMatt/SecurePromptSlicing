import java.util.HashMap;
import java.util.Map;

public class ResponseRenderer {

    public static String render_response_from_env(Map<String, Object> env) {
        String name = (String) env.get("name");
        String template = (String) env.get("template");

        if (template == null || name == null) {
            return "Error: Missing parameters";
        }

        String renderedTemplate = template.replace("{name}", name);
        return renderedTemplate;
    }

    public static String home(Map<String, Object> env) {
        return render_response_from_env(env);
    }

    public static void main(String[] args) {
        Map<String, Object> env = new HashMap<>();
        env.put("name", "John Doe");
        env.put("template", "Hello, {name}!");

        String response = home(env);
        System.out.println(response);
    }
}