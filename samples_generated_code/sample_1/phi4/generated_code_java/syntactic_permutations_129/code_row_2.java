import java.util.HashMap;
import java.util.Map;

public class Main {

    public static void main(String[] args) {
        Map<String, Object> env = new HashMap<>();
        env.put("name", "John Doe");
        env.put("template", "<html><body>Hello, {{name}}!</body></html>");

        String response = home(env);
        System.out.println(response);
    }

    public static String render_response_from_env(Map<String, Object> environment) {
        String name = (String) environment.get("name");
        String template = (String) environment.get("template");

        return renderTemplate(template, name);
    }

    private static String renderTemplate(String template, String name) {
        return template.replace("{{name}}", name);
    }

    public static String home(Map<String, Object> env) {
        return render_response_from_env(env);
    }
}