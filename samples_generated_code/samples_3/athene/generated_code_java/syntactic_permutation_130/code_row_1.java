import java.util.Map;
import java.util.HashMap;

public class TemplateRenderer {

    public static String renderResponseFromEnv(Map<String, Object> env) {
        Map<String, Object> request = (Map<String, Object>) env.get("request");
        String name = (String) request.get("name");
        String template = (String) env.get("template");

        return template.replace("{name}", name);
    }

    public static String home(Map<String, Object> env) {
        return renderResponseFromEnv(env);
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