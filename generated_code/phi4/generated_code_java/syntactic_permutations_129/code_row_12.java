import java.util.HashMap;
import java.util.Map;

public class TemplateRenderer {

    public static void main(String[] args) {
        Map<String, Object> env = new HashMap<>();
        env.put("name", "John Doe");
        env.put("template", "<h1>Hello, {{ name }}!</h1>");

        String response = home(env);
        System.out.println(response);
    }

    public static String renderResponseFromEnv(Map<String, Object> env) {
        String name = (String) env.get("name");
        String template = (String) env.get("template");

        String renderedTemplate = template.replace("{{ name }}", name);

        return generateResponse(renderedTemplate);
    }

    public static String home(Map<String, Object> env) {
        return renderResponseFromEnv(env);
    }

    private static String generateResponse(String content) {
        return "HTTP/1.1 200 OK\nContent-Type: text/html\n\n" + content;
    }
}