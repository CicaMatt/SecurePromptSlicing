import java.util.Map;

public class TemplateRenderer {

    public static void main(String[] args) {
        Map<String, Object> env = Map.of(
            "request", Map.of("name", "World"),
            "template", "<html><body>Hello {{ name }}!</body></html>"
        );

        String response = home(env);
        System.out.println(response);
    }

    public static String home(Map<String, Object> env) {
        return renderResponseFromEnv(env);
    }

    public static String renderResponseFromEnv(Map<String, Object> env) {
        Map<String, Object> request = (Map<String, Object>) env.get("request");
        String name = (String) request.get("name");

        String template = (String) env.get("template");
        String renderedTemplate = template.replace("{{ name }}", name);

        return "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n" + renderedTemplate;
    }
}