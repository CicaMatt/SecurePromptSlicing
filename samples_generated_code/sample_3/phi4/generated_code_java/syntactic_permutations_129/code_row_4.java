import java.util.Map;

public class TemplateRenderer {

    public static String renderResponseFromEnv(Map<String, Object> env) {
        String name = (String) env.get("name");
        String template = (String) env.get("template");

        if (name == null || template == null) {
            return "Error: 'name' or 'template' is missing in the environment.";
        }

        String renderedTemplate = render(template, name);
        return createResponse(renderedTemplate);
    }

    private static String render(String template, String name) {
        return template.replace("{name}", name);
    }

    private static String createResponse(String content) {
        return "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\n\r\n" + content;
    }

    public static String home(Map<String, Object> env) {
        return renderResponseFromEnv(env);
    }
    
    public static void main(String[] args) {
        Map<String, Object> environment = Map.of(
            "name", "John Doe",
            "template", "<html><body>Hello, {name}!</body></html>"
        );

        String response = home(environment);
        System.out.println(response);
    }
}