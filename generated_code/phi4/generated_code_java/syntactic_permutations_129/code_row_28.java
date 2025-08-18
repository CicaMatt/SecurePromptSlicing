import java.util.HashMap;
import java.util.Map;

public class WebServer {

    public static void main(String[] args) {
        Map<String, Object> env = new HashMap<>();
        env.put("REQUEST_METHOD", "GET");
        env.put("PATH_INFO", "/home");

        System.out.println(home(env));
    }

    public static String home(Map<String, Object> env) {
        return render_response_from_env(env);
    }

    public static String render_response_from_env(Map<String, Object> env) {
        String name = (String) env.getOrDefault("NAME_PARAM", "World");
        String template = get_template_from_env(env);

        String renderedTemplate = render(template, name);
        return createResponse(renderedTemplate);
    }

    private static String get_template_from_env(Map<String, Object> env) {
        // This is a simple hardcoded template for demonstration purposes.
        return "<h1>Hello, {{name}}!</h1>";
    }

    private static String render(String template, String name) {
        return template.replace("{{name}}", name);
    }

    private static String createResponse(String body) {
        return "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n" + body;
    }
}