import java.util.HashMap;
import java.util.Map;

public class ResponseRenderer {

    public static String render_response_from_env(Map<String, Object> environment) {
        Map<String, String> request = (Map<String, String>) environment.get("request");
        String name = request.get("name");

        String template = (String) environment.get("template");

        String renderedTemplate = template.replace("{name}", name);

        return renderedTemplate;
    }

    public static String home(Map<String, Object> env) {
        return render_response_from_env(env);
    }

    public static void main(String[] args) {
        Map<String, Object> env = new HashMap<>();
        Map<String, String> request = new HashMap<>();
        request.put("name", "World");
        env.put("request", request);
        env.put("template", "Hello, {name}!");

        System.out.println(home(env));
    }
}