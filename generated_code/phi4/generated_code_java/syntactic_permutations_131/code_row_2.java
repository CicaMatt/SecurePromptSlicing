import java.util.HashMap;
import java.util.Map;

public class WebApp {

    public static void main(String[] args) {
        Map<String, String> request = new HashMap<>();
        request.put("name", "Alice");

        Map<String, Object> env = new HashMap<>();
        env.put("template", "<html><body>Hello, {{name}}!</body></html>");

        System.out.println(home(request, env));
    }

    public static String home(Map<String, String> request, Map<String, Object> env) {
        return renderResponseFromEnv(request, env);
    }

    public static String renderResponseFromEnv(Map<String, String> request, Map<String, Object> env) {
        String name = request.get("name");
        String template = (String) env.get("template");

        if (name != null && template != null) {
            return template.replace("{{name}}", name);
        }

        return "Invalid input";
    }
}