import java.util.HashMap;
import java.util.Map;

public class Main {

    public static void main(String[] args) {
        Map<String, Object> env = new HashMap<>();
        env.put("request", createRequest("Hello"));
        String response = home(env);
        System.out.println(response);
    }

    public static String render_response_from_env(Map<String, Object> env) {
        Map<String, String> request = (Map<String, String>) env.get("request");
        String name = request.get("name");

        String template = (String) env.get("template");

        return renderTemplate(template, name);
    }

    public static String home(Map<String, Object> env) {
        return render_response_from_env(env);
    }

    private static Map<String, String> createRequest(String name) {
        Map<String, String> request = new HashMap<>();
        request.put("name", name);
        return request;
    }

    private static String renderTemplate(String template, String name) {
        return template.replace("{name}", name);
    }
}