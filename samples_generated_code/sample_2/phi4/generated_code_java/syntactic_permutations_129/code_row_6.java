import java.util.HashMap;
import java.util.Map;

public class TemplateRenderer {

    public static void main(String[] args) {
        Map<String, String> env = new HashMap<>();
        env.put("template_name", "welcome.html");

        System.out.println(home(env));
    }

    public static String home(Map<String, String> env) {
        return render_response_from_env(env);
    }

    private static String render_response_from_env(Map<String, String> env) {
        String templateName = env.getOrDefault("template_name", "default.html");
        String renderedTemplate = renderTemplate(templateName);
        return createResponse(renderedTemplate);
    }

    private static String renderTemplate(String templateName) {
        // Simulating template rendering
        switch (templateName) {
            case "welcome.html":
                return "<html><body>Welcome to our site!</body></html>";
            default:
                return "<html><body>This is the default page.</body></html>";
        }
    }

    private static String createResponse(String content) {
        return "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n" + content;
    }
}