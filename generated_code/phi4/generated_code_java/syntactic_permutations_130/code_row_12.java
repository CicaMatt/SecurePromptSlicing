import java.util.Map;

public class TemplateRenderer {

    public static void main(String[] args) {
        Map<String, Object> env = Map.of("name", "World", "template", "<h1>Hello, {{ name }}!</h1>");
        String response = home(env);
        System.out.println(response);
    }

    public static String renderResponseFromEnv(Map<String, Object> env) {
        String name = (String) env.get("name");
        String template = (String) env.get("template");

        if (name == null || template == null) {
            return "Missing name or template";
        }
        
        String renderedTemplate = template.replace("{{ name }}", name);
        return createResponse(renderedTemplate);
    }

    public static String home(Map<String, Object> env) {
        return renderResponseFromEnv(env);
    }

    private static String createResponse(String body) {
        return "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\nContent-Length: " + body.length() + "\r\n\r\n" + body;
    }
}