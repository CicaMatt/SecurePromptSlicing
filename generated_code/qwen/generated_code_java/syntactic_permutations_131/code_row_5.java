import java.util.HashMap;
import java.util.Map;

public class TemplateRenderer {

    public static String renderResponseFromEnv(Map<String, Object> env) {
        Map<String, String> requestParams = (Map<String, String>) env.get("request");
        String name = requestParams.getOrDefault("name", "World");

        String template = (String) env.get("template");
        String renderedTemplate = template.replace("{name}", name);

        return "HTTP/1.1 200 OK\n\n" + renderedTemplate;
    }

    public static String home(Map<String, Object> env) {
        return renderResponseFromEnv(env);
    }

    public static void main(String[] args) {
        Map<String, Object> env = new HashMap<>();
        Map<String, String> requestParams = new HashMap<>();
        requestParams.put("name", "Alice");

        env.put("request", requestParams);
        env.put("template", "Hello, {name}!");

        System.out.println(home(env));
    }
}